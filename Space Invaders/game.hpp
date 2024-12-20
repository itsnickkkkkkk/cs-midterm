#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game {
	public:
		Game();
		~Game();
		void Draw(); // draw loop
		void Update(); // update loop
		void HandleInput(); // wasd or arrow keys
		bool run; // game is running
		int lives; // how many lives
		int score; // score
		int highScore; // highscore
		bool secretMode; // cooldown disabled
	private:
		void DeleteInactiveLasers(); // function to remove lasers
		std::vector<Obstacle> CreateObstacles();  // makes the shield bubble thingys
		std::vector<Alien> CreateAliens(); // makes alien
		void moveAliens(); // moves them laterally
		void moveDownAliens(int distance); // moves them down
		void alienShoot(); // makes aliens shoot
		void CollisionCheck(); // diy collisions
		void highScoreCheck(); // check txt file for high score
		void saveScore(int highScore); // save the high score
		int loadScore(); // load the score
		Spaceship spaceship;
		std::vector<Obstacle> obstacles;
		std::vector<Alien> aliens;
		int alienDirection; // make aliens move left or right
		std::vector<Laser> alienLasers;
		constexpr static float alienShootInterval = 0.35; // make aliens have a cooldown
		float timeAlienFired; // declare variable!!
		MysteryShip mysteryship;
		float mystertyShipSpawn;
		float timeLastSpawn;
		void YouLose(); // gg
		void Restart(); // restart the game
		void InitializeGame(); // initialize the game
};