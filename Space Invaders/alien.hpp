#pragma once
#include <raylib.h>

class Alien {
	public:
		Alien(int type, Vector2 position);
		void Update(int direction);
		void Draw();
		int GetType();
		static void UnloadImages();
		Rectangle getRect(); // collision
		static Texture2D alienImages[3]; // 3 textures for alien
		int type;
		Vector2 position;
};