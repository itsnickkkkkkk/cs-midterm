#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
	// draw the ship
	image = LoadTexture("Graphics/SpookyShip.png"); 
	living = false;
}

MysteryShip::~MysteryShip() {
	// bye bye ship
	UnloadTexture(image);
}

void MysteryShip::Spawn() {
	// puts it at the top
	position.y = 70;
	// what side will it spawn at
	int side = GetRandomValue(0, 1);
	// left side
	if (side == 0) {
		position.x = 25;
		speed = 3;
	}
	else { // right side
		position.x = GetScreenWidth() - image.width - 25;
		speed = -3;
	}
	living = true;
}

Rectangle MysteryShip::getRect()
{
	// collision
	if (living) {
		return { position.x, position.y, float(image.width), float(image.height) };
	}
	else {
		return { position.x, position.y, 0, 0 };
	}
}

void MysteryShip::Update() {
	if (living) {
		position.x += speed; // move it move it
		if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25) {
			living = false; // remove if it goes off screen
		}
	}
}

void MysteryShip::Draw() {
	if (living) {
		DrawTextureV(image, position, WHITE);
	}
}


