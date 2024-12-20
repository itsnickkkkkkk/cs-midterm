#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
	this->position = position;
	this->speed = speed;
	active = true; // sets laser to be active
}

void Laser::Draw() {
	if (active) {
		DrawRectangle(position.x, position.y, 4, 15, { 255, 255, 255 ,255 }); // draws the laser 
	}
}

Rectangle Laser::getRect()
{
	// draw collision box around laser
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}

void Laser::Update() {
	position.y += speed; // laser shoot and go pew pew
	if (active) {
		// remove laser if off screen
		if (position.y > GetScreenHeight() - 100 || position.y < 25) {
			active = false; 
		}
	}
}
