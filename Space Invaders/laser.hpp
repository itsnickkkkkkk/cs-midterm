#pragma once
#include <raylib.h>

class Laser {
	public:
		Laser(Vector2 position, int speed);
		void Update();
		void Draw();
		Rectangle getRect(); //collisions
		bool active;
	private:
		Vector2 position;
		int speed; // speed of laser
};