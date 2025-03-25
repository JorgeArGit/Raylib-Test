#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>

class Obstacle {


	float positionX;
	float speed;
	int randomDirection;
	int randomPosition;

public:
	Obstacle() {

		this->positionX = 760.0f;
		this->speed = 100.0f;
		this->randomDirection = (rand() % 2) * 2;
		this->randomPosition = rand() % 51;
		
	}

	void updatePosition() {

		this->positionX -= this->speed * GetFrameTime();
	}

	std::string returnInfo() {

		return std::to_string(this->speed) + "\n" + std::to_string(this->positionX);
	}

	void drawObstacle() {

		
		DrawRectangle(this->positionX, -250 + (randomDirection * randomPosition), 64, 360, BLACK);
		DrawRectangle(this->positionX, 250 + (randomDirection * randomPosition), 64, 360, BLACK);
	}

	int returnPosition() {
		
		return positionX;
	}


};

int screenWidth = 640;
int screenHeight = 360;

Vector2 rectanglePosition = { (float)50, (float)100 };

//Player variables
float gravity = 15.0f;
float jumpVelocity = -400.0f;
float velocity = 0.0f;
//Player variables

//Obstacle variables
const int maxObstacles = 10;
float spawnTime = 0.0f;
std::vector<Obstacle> obstaclesContainer;
//Obstacle variables

//Function declaration
void jump();
void spawnObstacle();
//Function declaration




void gameTwo() {

	

	InitWindow(screenWidth, screenHeight, "Test");

	SetTargetFPS(60);

	while (WindowShouldClose() != true) {

		

		BeginDrawing();

		ClearBackground(YELLOW);
		DrawRectangle(rectanglePosition.x, rectanglePosition.y, 32, 32, BLACK);
		for (int i = 0; i < obstaclesContainer.size(); i++) {
			obstaclesContainer[i].drawObstacle();
		}



		EndDrawing();

		jump();
		spawnObstacle();
		
		for (int i = 0; i < obstaclesContainer.size(); i++) {
			obstaclesContainer[i].updatePosition();
			if (obstaclesContainer[i].returnPosition() < -100)
				obstaclesContainer.erase(obstaclesContainer.begin());
		}

		std::cout << obstaclesContainer.size();
		
	}

	CloseWindow();


}

void jump() {

	rectanglePosition.y += velocity * GetFrameTime();
	velocity += gravity;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true) velocity = jumpVelocity;


}

void spawnObstacle() {
	
	
	spawnTime += GetFrameTime();



	if (spawnTime >= 2.0) {

		obstaclesContainer.push_back(Obstacle());
		spawnTime = 0;
		
	}
	
	
}
