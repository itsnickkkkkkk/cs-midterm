#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
	this->position = position;
	this->speed = speed;
	active = true;
}

void Laser::Draw() {
	if (active) {
		DrawRectangle(position.x, position.y, 4, 15, { 122, 255, 0,255 }); // draws the laser 
	}
}

void Laser::Update() {
	position.y += speed; // laser shoot and go pew pew
	if (active) {
		if (position.y > GetScreenHeight() || position.y < 0) {
			active = false;
		}
	}
}
