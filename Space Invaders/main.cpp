#include <raylib.h>
#include <string>
#include "game.hpp"

std::string Formatting(int number, int width) {
	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {
	int windowWidth = 750;
	int windowHeight = 700;
	int offset = 50;

	InitWindow(windowWidth + offset, windowHeight + 2 * offset, "NOT space invaders");
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Texture2D spaceshipPic = LoadTexture("Graphics/spaceship.png");
	SetTargetFPS(60);

	Game game;

	while (WindowShouldClose() == false) {

		game.HandleInput();
		game.Update();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 2, WHITE);
		DrawLineEx({ 25, 730 }, { 775, 730 }, 3, WHITE);
		if (game.run) {
			DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, WHITE);
		}
		else {
			DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, WHITE);
		}
		float x = 50.0;
		for (int i = 0; i < game.lives; i++) {
			DrawTextureV(spaceshipPic, { x, 745 }, WHITE);
			x += 50;
		}

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