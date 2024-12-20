#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship {
	public:
		Spaceship();
		~Spaceship();
		void Draw();
		void moveLeft(); // move the ship left
		void moveRight(); // move the ship right
		void fireLaser(); // pew pew
		Rectangle getRect(); // collision box
		void Restart(); // restarting game
		std::vector<Laser> lasers;
	private:
		Texture2D image;
		Vector2 position;
		double lastFireTime; // user cooldown
};