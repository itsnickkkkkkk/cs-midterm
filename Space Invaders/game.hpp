#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"

class Game {
	public:
		Game();
		~Game();
		void Draw();
		void Update();
		void HandleInput();
	private:
		void DeleteInactiveLasers();
		std::vector<Obstacle> CreateObstacles();
		std::vector<Alien> CreateAliens();
		void moveAliens();
		void moveDownAliens(int distance);
		void alienShoot();
		Spaceship spaceship;
		std::vector<Obstacle> obstacles;
		std::vector<Alien> aliens;
		int alienDirection;
		std::vector<Laser> alienLasers;
		constexpr static float alienShootInterval = 0.35;
		float timeAlienFired;
};