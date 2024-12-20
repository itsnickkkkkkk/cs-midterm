#include "spaceship.hpp"

Spaceship::Spaceship()
{
	image = LoadTexture("Graphics/spaceship.png"); // draws the spaceship
	position.x = (GetScreenWidth() - image.width)/2;
	position.y = (GetScreenHeight() - image.height - 100);
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::moveLeft() {
	position.x -= 7; // speed of the movement
	if (position.x < 25) {
		position.x = 25;
	}
}

void Spaceship::moveRight() {
	position.x += 7; // speed of the movement
	if (position.x > GetScreenWidth() - image.width - 25) {
		position.x = GetScreenWidth() - image.width - 25;
	}
}

void Spaceship::fireLaser()
{
	if (GetTime() - lastFireTime >= 0.35) { // cools down so you dont have a laser beam
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
		lastFireTime = GetTime();
	}
	
}

Rectangle Spaceship::getRect()
{
	// collision stuff
	return { position.x, position.y ,float(image.width),float(image.height) };
}

void Spaceship::Restart()
{
	// reset the spaceship 
	position.x = (GetScreenWidth() - image.width) / 2.0f;
	position.y = GetScreenHeight() - image.height - 100;
	lasers.clear();
}

