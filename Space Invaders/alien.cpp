#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
	this->type = type;
	this->position = position;

	if (alienImages[type - 1].id == 0) {
		switch (type) {
		case 1:
			alienImages[0] = LoadTexture("Graphics/Alien1.png"); // loads first row
			break;
		case 2:
			alienImages[1] = LoadTexture("Graphics/Alien2.png"); // loads second
			break;
		case 3:
			alienImages[2] = LoadTexture("Graphics/Alien3.png"); // loads third row
			break;
		default:
			alienImages[0] = LoadTexture("Graphics/Alien1.png"); // default row to first 
			break;
		}
	}
}

void Alien::Update(int direction)
{
	position.x += direction;
}

void Alien::Draw() {
	DrawTextureV(alienImages[type-1], position, WHITE);
}

int Alien::GetType() {
	return type; // which alien is in
}

void Alien::UnloadImages()
{
	for (int i = 0; i < 4; i++) {
		UnloadTexture(alienImages[i]);
	}
}

Rectangle Alien::getRect()
{
	// draw the collision box around alien
	return { position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height) }; 
};