#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
	InitializeGame(); // draw the game
}

Game::~Game() {
	Alien::UnloadImages();
}

void Game::Update() {
	if (run) { // if user is alive
		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > mystertyShipSpawn) { // mystery ship random spawn 
			mysteryship.Spawn();
			timeLastSpawn = GetTime();
			mystertyShipSpawn = GetRandomValue(10, 20);
		}

		for (auto& laser : spaceship.lasers) { 
			laser.Update();
		}
		moveAliens(); // moves the aliens every frame
		alienShoot(); // lets the aliens shoot

		for (auto& laser : alienLasers) {
			laser.Update();
		}
		DeleteInactiveLasers(); // clears lasers
		mysteryship.Update();
		CollisionCheck(); // check for collisions
	}
	else {
		if (IsKeyDown(KEY_ENTER)) { // restart game function
			Restart();
			InitializeGame();
		}
	}
	
}

void Game::Draw() { // function draws everything
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien: aliens) {
		alien.Draw();
	}
	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	mysteryship.Draw();
}

void Game::HandleInput() { // moves or fires the spaceship
	if (run) {
		if (IsKeyDown(KEY_A)) {
			spaceship.moveLeft();
		}
		else if (IsKeyDown(KEY_D)) {
			spaceship.moveRight();
		}
		else if (IsKeyDown(KEY_SPACE)) {
			spaceship.fireLaser();
		}
	}
}

void Game::DeleteInactiveLasers() { // remove extra laser
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
		if (!it->active) {
			it = spaceship.lasers.erase(it);
		}
		else {
			++it;
		}
	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (!it->active) {
			it = alienLasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles() // draws the obstacles
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
	}
	return obstacles;
}

std::vector<Alien> Game::CreateAliens() // draws all the aliens in a grid
{
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {
			
			int alienType;
			if (row == 0) {
				alienType = 3;
			}
			else if (row == 1 || row == 2) {
				alienType = 2;
			}
			else {
				alienType = 1;
			}
			
			float x = 75 + column * 55;
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, {x, y}));
		}
	}
	return aliens;
}

void Game::moveAliens() { // moves the aliens
	for (auto& alien : aliens) {
		// make sure the aliens dont fly into space
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
			alienDirection = -1;
		}
		// make sure the aliens dont fly into space the other way
		if (alien.position.x < 25) {
			alienDirection = 1;
			moveDownAliens(4);
		}

		alien.Update(alienDirection);
	}
}

void Game::moveDownAliens(int distance)
{
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void Game::alienShoot()
{
	// cool down bc shoot way too damn fast
	double currentTime = GetTime();
	if (IsKeyDown(KEY_G)) {
		secretMode = true;
	}
	// disable cooldown for funsies
	if (secretMode) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
	} else if (currentTime - timeAlienFired >= alienShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
		timeAlienFired = GetTime(); 
	}
	
}

void Game::CollisionCheck()
{
	// ship lasers
	for (auto& laser : spaceship.lasers) {
		auto it = aliens.begin();
		while (it != aliens.end()) {
			// score when kill alien woohoo
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
				if (it->type == 1) {
					score += 100;
				}
				else if (it->type == 2) {
					score += 200;
				}
				else if (it->type == 3) {
					score += 300;
				}
				
				highScoreCheck(); // checks if score is higher than high

				it = aliens.erase(it);
				laser.active = false;
			}
			else {
				++it;
			}
		}
		
		for (auto& obstacle : obstacles) { // checks if laser hits the shield 
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {  // checks if laser hits the mystery
			mysteryship.living = false; // removes the ship
			laser.active = false; // disable the laser
			score += 500; // scores
			highScoreCheck(); // checks high score
		}
	}
	// bad guy beam
	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) { // if alien hit player
			laser.active = false; // disable laser
			lives --; // remove a life
			if (lives == 0) {
				YouLose(); // game over gg
			}
		}

		for (auto& obstacle : obstacles) { // alien laser collide with barrier
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}
	}

	// alien go sweep sweep

	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) { // if aliens themselves hit the block
					it = obstacle.blocks.erase(it); // remove all the blocks that collide
				}
				else {
					it++;
				}
			}
		}
	}
		
}

void Game::highScoreCheck()
{
	// set a new high score
	if (score > highScore) {
		highScore = score;
		saveScore(highScore);
	}
}

void Game::saveScore(int highScore)
{
	// save high score to a file
	std::ofstream highScoreFile("highscore.txt");
	if (highScoreFile.is_open()) {
		highScoreFile << highScore;
		highScoreFile.close();
	}
	else {
	std::cerr << "Failed to save" << std::endl;
	}
}

int Game::loadScore()
{
	// load the new highscore
	int loadedScore = 0; // initialize
	std::ifstream highScoreFile("highscore.txt"); // open the file
	if (highScoreFile.is_open()) {
		highScoreFile >> loadedScore; 
		highScoreFile.close();
	}
	else {
		std::cerr << "Failed to load" << std::endl;
	}
	return loadedScore;
}

void Game::YouLose()
{
	run = false; // turn off the game
}

void Game::Restart()
{
	spaceship.Restart(); // resets position
	aliens.clear(); // resets aliens
	alienLasers.clear(); // removes lasers
	obstacles.clear(); // removes obstacles
}

void Game::InitializeGame()
{
	obstacles = CreateObstacles(); // draws the obstacles
	aliens = CreateAliens(); // draws the aliens
	alienDirection = 1;
	timeAlienFired = 0.0; // sets the time to 0
	timeLastSpawn = 0.0; // mysteryship spawn
	mystertyShipSpawn = GetRandomValue(10, 20);
	lives = 3; // set to 3 lives
	score = 0; // initialize score
	run = true; // set game running
	highScore = loadScore();
}