#include <raylib.h>
#include "game.hpp"

int main() {
	int windowWidth = 750;
	int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "NOT space invaders");
	SetTargetFPS(60);

	Game game;

	while (WindowShouldClose() == false) {

		game.HandleInput();
		game.Update();
		BeginDrawing();
		ClearBackground(BLACK);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

}