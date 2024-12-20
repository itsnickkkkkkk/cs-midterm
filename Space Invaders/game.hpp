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
		bool run;
		int lives;
		int score;
		int highScore;
		bool secretMode;
	private:
		void DeleteInactiveLasers();
		std::vector<Obstacle> CreateObstacles(); 
		std::vector<Alien> CreateAliens();
		void moveAliens();
		void moveDownAliens(int distance);
		void alienShoot();
		void CollisionCheck();
		void highScoreCheck();
		void saveScore(int highScore);
		int loadScore();
		Spaceship spaceship;
		std::vector<Obstacle> obstacles;
		std::vector<Alien> aliens;
		int alienDirection;
		std::vector<Laser> alienLasers;
		constexpr static float alienShootInterval = 0.35;
		float timeAlienFired; // declare variable!!
		MysteryShip mysteryship;
		float mystertyShipSpawn;
		float timeLastSpawn;
		void YouLose();
		void Restart();
		void InitializeGame();
};