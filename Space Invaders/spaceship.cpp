#include "spaceship.hpp"

Spaceship::Spaceship()
{
	image = LoadTexture("Graphics/spaceship.png"); // draws the spaceship
	position.x = (GetScreenWidth() - image.width)/2;
	position.y = (GetScreenHeight() - image.height);
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::moveLeft() {
	position.x -= 7; // speed of the movement
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::moveRight() {
	position.x += 7; // speed of the movement
	if (position.x > GetScreenWidth() - image.width) {
		position.x = GetScreenWidth() - image.width;
	}
}

void Spaceship::fireLaser()
{
	if (GetTime() - lastFireTime >= 0.35) { // cools down so you dont have a laser beam
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
		lastFireTime = GetTime();
	}
	
}

