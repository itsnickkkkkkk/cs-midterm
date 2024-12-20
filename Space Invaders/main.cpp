#include <raylib.h>
#include <string>
#include "game.hpp"

std::string Formatting(int number, int width) {
	std::string numberText = std::to_string(number); 
	int leadingZeros = width - numberText.length(); // old school arcade score look
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {
	int windowWidth = 750; // fixed x value
	int windowHeight = 700; // fixed y value
	int offset = 50; // barrier at bottom

	InitWindow(windowWidth + offset, windowHeight + 2 * offset, "NOT space invaders"); // create game window
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0); // load the arcade font
	Texture2D spaceshipPic = LoadTexture("Graphics/spaceship.png"); // load the lives
	SetTargetFPS(60); // cap fps at 60

	Game game;

	while (WindowShouldClose() == false) { // if window is open

		game.HandleInput();
		game.Update();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 2, WHITE); // border
		DrawLineEx({ 25, 730 }, { 775, 730 }, 3, WHITE); // hrizontal line
		if (game.run) {
			DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, WHITE); // too lazy to make other levels
		}
		else {
			DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, WHITE); // you lose
		}
		float x = 50.0;
		for (int i = 0; i < game.lives; i++) { // draw the lives
			DrawTextureV(spaceshipPic, { x, 745 }, WHITE);
			x += 50; // moves png over by 50 pixels
		}
		// score text
		DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, WHITE);
		std::string scoreText = Formatting(game.score, 5);
		DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, WHITE);

		DrawTextEx(font, "HIGH SCORE", { 570, 15 }, 34, 2, WHITE);
		std::string highScoreText = Formatting(game.highScore, 5);
		DrawTextEx(font, highScoreText.c_str(), { 655, 40 }, 34, 2, WHITE);

		game.Draw();
		EndDrawing();
	}

	CloseWindow();

}