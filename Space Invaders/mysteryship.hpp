#pragma once
#include <raylib.h>

class MysteryShip {
public:
	MysteryShip();
	~MysteryShip();
	void Update();
	void Draw();
	void Spawn();
	Rectangle getRect(); // collision
	bool living; // check if mysteryship is spawned in
private:
	Vector2 position;
	Texture2D image;
	int speed; // speed of the ship
};