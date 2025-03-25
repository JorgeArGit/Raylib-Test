#include "raylib.h"

void gameOne(){

	int screenWidth = 640;
	int screenHeight = 360;

	Vector2 rectanglePosition = { (float)300, (float)100 };

	InitWindow(screenWidth, screenHeight, "Test");

	SetTargetFPS(60);

	while (WindowShouldClose() != true) {

		if (IsKeyDown(KEY_A) == true) rectanglePosition.x -= 10.0f;
		if (IsKeyDown(KEY_D) == true) rectanglePosition.x += 10.0f;
		if (IsKeyDown(KEY_W) == true) rectanglePosition.y -= 10.0f;
		if (IsKeyDown(KEY_S) == true) rectanglePosition.y += 10.0f;

		BeginDrawing();

		ClearBackground(YELLOW);

		DrawText("This is a test", 120, 130, 42, BLACK);
		DrawRectangle(rectanglePosition.x, rectanglePosition.y, 32, 32, BLACK);

		EndDrawing();

	}

	CloseWindow();


}