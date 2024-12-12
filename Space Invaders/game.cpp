#include "game.hpp"
#include <iostream>

Game::Game()
{
	obstacles = CreateObstacles(); // draws the obstacles
	aliens = CreateAliens(); // draws the aliens
	alienDirection = 1;
	timeAlienFired = 0.0; // sets the time to 0
}

Game::~Game() {
	Alien::UnloadImages();
}

void Game::Update() {
	for (auto& laser : spaceship.lasers) {
		laser.Update();
	}
	moveAliens(); // moves the aliens every frame
	alienShoot(); // lets the aliens shoot

	for (auto& laser : alienLasers) {
		laser.Update();
	}
	DeleteInactiveLasers(); // clears lasers
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
}

void Game::HandleInput() { // moves or fires the spaceship
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

void Game::DeleteInactiveLasers() {
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
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 100) }));
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
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()) {
			alienDirection = -1;
		}
		// make sure the aliens dont fly into space the other way
		if (alien.position.x < 0) {
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
	if (currentTime - timeAlienFired >= alienShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
		timeAlienFired = GetTime(); 
	}
	
}
