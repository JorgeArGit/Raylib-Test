#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>

class Obstacle {


	float positionX;
	float speed;
	int randomDirection;
	int randomPosition;
	Rectangle obstacleOne;
	Rectangle obstacleTwo;
	Rectangle collisionOne;
	Rectangle collisionTwo;
	Rectangle score;
	bool canScore;


public:
	Obstacle() {

		positionX = 760.0f;
		speed = 100.0f;
		randomDirection = (rand() % 2) * 2;
		randomPosition = rand() % 51;
		obstacleOne = {positionX, -250.0f + (randomDirection * randomPosition), 64, 400 };
		obstacleTwo = {positionX, 250.0f + (randomDirection * randomPosition), 64, 400 };
		collisionOne = {positionX + 5, -260.0f + (randomDirection * randomPosition), 54, 400 };
		collisionTwo = {positionX + 5, 260.0f + (randomDirection * randomPosition), 54, 400 };
		score = {positionX, 0.0f , 1, 360 };
		canScore = true;
		
	}

	void updatePosition() {

		obstacleOne.x -= speed * GetFrameTime();
		obstacleTwo.x -= speed * GetFrameTime();
		collisionOne.x -= speed * GetFrameTime();
		collisionTwo.x -= speed * GetFrameTime();
		score.x -= speed * GetFrameTime();
	}

	void drawObstacle() {

		
		DrawRectangleRec(obstacleOne, BLACK);
		DrawRectangleRec(obstacleTwo, BLACK);
		
		
	}

	int returnPosition() {
		
		return obstacleOne.x;
	}

	bool checkCollision(Rectangle player) {

		if (CheckCollisionRecs(collisionOne, player) == true || CheckCollisionRecs(collisionTwo, player) == true) return true;
	}

	bool checkScore(Rectangle player) {

		if (canScore) {
			if (CheckCollisionRecs(score, player) == true) return true;
		}
		else
			return false;
	}

	void setCanScore() {

		canScore = false;
	}

};

int screenWidth = 640;
int screenHeight = 360;



//Player variables
Vector2 rectanglePosition = { (float)50, (float)100 };
Rectangle player = { rectanglePosition.x, rectanglePosition.y, 32, 16 };
float gravity = 15.0f;
float jumpVelocity = -375.0f;
float velocity = 0.0f;
int score = 0;
//Player variables

//Obstacle variables
const int maxObstacles = 10;
float spawnTime = 0.0f;
std::vector<Obstacle> obstaclesContainer;
bool canScore = true;
//Obstacle variables

//Function declaration
void jump();
void spawnObstacle();
//Function declaration

//Sound
Sound jumpSound;
Sound scoreSound;
//Sound

//Textures
Texture birdTexture;
//Textures


void gameTwo() {

	

	InitWindow(screenWidth, screenHeight, "Test");
	InitAudioDevice();
	jumpSound = LoadSound("C:/Users/jorge/Music/jumpSound.wav");
	scoreSound = LoadSound("C:/Users/jorge/Music/scoreSound.wav");
	birdTexture = LoadTexture("C:/Users/jorge/Pictures/bird.png");

	
	SetTargetFPS(60);

	while (WindowShouldClose() != true) {


		if (player.y < -15.0f)
			CloseWindow();
		else if (player.y > 346.0f)
			CloseWindow();

		BeginDrawing();

		

		ClearBackground(SKYBLUE);
		//DrawRectangleRec(player, RED);
		DrawTexture(birdTexture, player.x, player.y - 10, WHITE);
		
		for (int i = 0; i < obstaclesContainer.size(); i++) {
			obstaclesContainer[i].drawObstacle();
			
		}

		const char* scoreChar = TextFormat("%d", score);
		DrawFPS(610, 10);
		DrawText(scoreChar, 320, 10, 24, WHITE);

		EndDrawing();

		jump();
		spawnObstacle();
		

		

		for (int i = 0; i < obstaclesContainer.size(); i++) {
			obstaclesContainer[i].updatePosition();
			if (obstaclesContainer[i].returnPosition() < -100)
				obstaclesContainer.erase(obstaclesContainer.begin());
			if (obstaclesContainer[i].checkCollision(player)) {
				CloseWindow();
			}

			if (obstaclesContainer[i].checkScore(player)) {
				obstaclesContainer[i].setCanScore();
				score++;
				PlaySound(scoreSound);
				

			}
			
				
		}

		
	}

	UnloadSound(scoreSound);
	UnloadSound(jumpSound);
	CloseWindow();
	CloseAudioDevice();


}

void jump() {

	player.y += velocity * GetFrameTime();
	velocity += gravity;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		velocity = jumpVelocity;
		PlaySound(jumpSound);
		
		
	}
	


}

void spawnObstacle() {
	
	
	spawnTime += GetFrameTime();



	if (spawnTime >= 2.0) {

		obstaclesContainer.push_back(Obstacle());
		spawnTime = 0;
		
	}
	
	
}
