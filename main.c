#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define DESIRED_SPEED 120
#define REACTION_TIME 0.7
#define MAX_CARS 1000
#define FRAMES 60
#define SPAWNTIME 1.3
#define SPAWNTIMER 1.3
#define CAR_LENGTH 80

typedef struct Car {
	bool disabled;
	int individualSpeed;
	int individualReactionTime;
	float reactionTime;
	float reactionTimer;
	Color color;
	Vector2 speed;
	Vector2 desiredSpeed;
	Vector2 position;
	Vector2 acceleration;
} Car;

float distanceBetweenCars(Car currentCar, Car previousCar) {
	return (previousCar.position.x - currentCar.position.x);
}

int randRange(int n)
{
    int limit;
    int r;
    limit = RAND_MAX - (RAND_MAX % n);

    while((r = rand()) >= limit);
    return r % n;
}

int main(void)
{
	int desiredSpeed = DESIRED_SPEED;
	float reactionTime = REACTION_TIME;
	float spawntime = SPAWNTIME;
	float spawntimer = SPAWNTIMER;
	const int screenWidth = 2400;
	const int screenHeight = 1450;
	Car *cars = (Car *)RL_CALLOC(MAX_CARS, sizeof(Car));
	int currentCars = 1;

	InitWindow(screenWidth, screenHeight, "Traffic Jam Simulation");
	SetTargetFPS(FRAMES);
	bool initCars = true;
	while(!WindowShouldClose()) {
		float dt = GetFrameTime();
		spawntimer -=dt;

		if(initCars) {
			initCars = false;
			currentCars = 1;
			spawntimer = spawntime;
			for(int i = 0; i < MAX_CARS; i++) {
			int individualSpeed = randRange(15);
			int individualReactionTime = randRange(5);
			cars[i] = (Car) {false, individualSpeed, individualReactionTime, reactionTime + 0.1 * individualReactionTime, reactionTime + 0.1 * individualReactionTime, LIGHTGRAY, (Vector2) {(desiredSpeed + individualSpeed)/3.6, 0.0}, (Vector2) {(desiredSpeed + individualSpeed)/3.6, 0.0}, (Vector2) {0.0, 500.0}};
			}
		}

		if(spawntimer < 0 && currentCars < MAX_CARS) {
			spawntimer = spawntime;
			currentCars++;
		}
		BeginDrawing();
		ClearBackground((Color) {86, 125, 70});

		for (int i = 0; i < 5; i++) {
			DrawRectangle(0, 390 + i * 200, screenWidth, 180, BLACK);
			for(int l = 0; l < 20; l++) {
			DrawRectangle(l*120, 480 + i * 200, 60, 10 ,WHITE);
			}
		}
		for(int i = 0; i < currentCars; i++) {
			float distanceToFront = 10000;
			if(i > 0) {
				distanceToFront = distanceBetweenCars(cars[i], cars[i-1]);
			}

			float reactionDistance_m = cars[i].speed.x * dt;
			float breakDistance_m = cars[i].speed.x * cars[i].speed.x  / (2.0 * 10);
			float stoppingDistance_m = reactionDistance_m + breakDistance_m;
			float pixelProMeter = 5.0;
			float stoppingDistance_px = stoppingDistance_m * pixelProMeter;
			
			cars[i].reactionTime = reactionTime + 0.1 * cars[i].individualReactionTime;
			cars[i].desiredSpeed.x = (desiredSpeed + cars[i].individualSpeed) / 3.6;
			
			if (cars[i].reactionTimer < 0 && distanceToFront < stoppingDistance_px * 0.7 && cars[i].position.y == cars[i-1].position.y) {
				cars[i].acceleration.x = -10.0;
				cars[i].color = (Color) {163, 24, 0, 255};
			} else if(cars[i].reactionTimer < 0 && distanceToFront < stoppingDistance_px && cars[i].position.y == cars[i-1].position.y) {
				cars[i].acceleration.x = -5.0;
				cars[i].color = (Color) {255, 40, 0, 255};
			} else if(cars[i].reactionTimer < 0 && distanceToFront < stoppingDistance_px * 1.5 && cars[i].position.y == cars[i-1].position.y) {
				cars[i].acceleration.x = -3;
				cars[i].color = (Color) {255, 116, 92 , 255};
			} else if(cars[i].speed.x >= cars[i].desiredSpeed.x && cars[i].reactionTimer < 0) {
				cars[i].acceleration.x = -3;
				cars[i].color = (Color) {255, 116, 92 , 255};
			} else if(cars[i].speed.x < cars[i].desiredSpeed.x * 0.7 && cars[i].reactionTimer < 0) {
				cars[i].acceleration.x = 3.0;
				cars[i].color = GREEN;
			} else if(cars[i].speed.x < cars[i].desiredSpeed.x && cars[i].reactionTimer < 0) {
				cars[i].acceleration.x = 5.0;
				cars[i].color = LIGHTGRAY;
			} else if(cars[i].speed.x < cars[i].desiredSpeed.x * 1.2 && cars[i].reactionTimer < 0) {
				cars[i].acceleration.x = 10.0;
				cars[i].color = PINK;
			}
			cars[i].speed.x += cars[i].acceleration.x * dt;
			cars[i].speed.y += cars[i].acceleration.y * dt;

			if(cars[i].speed.x < 0) {
				cars[i].speed.x = 0.0;
			}
			cars[i].position.x += cars[i].speed.x * dt * 5;
			if(cars[i].acceleration.x > 0 && cars[i].reactionTimer < 0) {
				cars[i].reactionTimer = cars[i].reactionTime;
			}
			cars[i].reactionTimer -= dt;
			if (cars[i].position.x > 2400) {
				cars[i].position.x = 0;
				cars[i].position.y += 200;
			}
			if(cars[i].position.x > 2400 & cars[i].position.y >= 1190) {
				cars[i].disabled = true;
			}
			if (!cars[i].disabled) {
				DrawRectangleV(cars[i].position, (Vector2) {(float) CAR_LENGTH, (float)50}, cars[i].color);
			}
		}
		
		if(IsKeyPressed(KEY_UP)) desiredSpeed++;
		if(IsKeyPressed(KEY_DOWN)) desiredSpeed--;
		if(IsKeyPressed(KEY_LEFT)) reactionTime -= 0.1;
		if(IsKeyPressed(KEY_RIGHT)) reactionTime += 0.1;
		if(IsKeyPressed(KEY_T)) spawntime -= 0.1;
		if(IsKeyPressed(KEY_Z)) spawntime += 0.1;
		if(IsKeyPressed(KEY_R)) initCars = true;
	// Draw UI

        DrawRectangle(10, 10, 680, 340, (Color){0,0, 0, 200 });
        DrawText("Controls:", 20, 20, 40, LIGHTGRAY);
        DrawText("- Right/Left: Change reaction time", 40, 60, 30, LIGHTGRAY);
        DrawText("- Up/Down: Change car desired speed", 40, 100, 30, LIGHTGRAY);
        DrawText("- R: restart traffic", 40, 140, 30, LIGHTGRAY);
	DrawText("- T/Z: Change spawntimer", 40, 180, 30, LIGHTGRAY);

	DrawText(TextFormat("[ FPS: %d ]\n", GetFPS()), 40, 200, 20, GREEN);
	DrawText(TextFormat("[ Reaction time: %f ]", reactionTime), 40, 240, 20, GREEN);
	DrawText(TextFormat("[ Desired speed: %d ]", desiredSpeed), 40, 280, 20, GREEN);
	DrawText(TextFormat("[ Spawntime: %f ]", spawntime), 40, 320, 20, GREEN);
	EndDrawing();
	}

	RL_FREE(cars);
	CloseWindow();

	return 0;
}

