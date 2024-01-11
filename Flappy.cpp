#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Flappy.h"




void Flappy::Main()
{
	InitWindow(screenWidth, screenHeight, "Flappy Bird");

	Start();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		Update();
	}

	CloseWindow();
}



void Flappy::Start()
{
	floppy.radius = BALL_RADIUS;
	floppy.position = Vector2{ 80, (float)screenHeight / 2 - floppy.radius };
	tubesSpeedX = 2;

	for (int i = 0; i < MAX_TUBES; i++)
	{
		tubesPos[i].x = 400 + 280 * i;
		tubesPos[i].y = -GetRandomValue(0, 120);
	}

	for (int i = 0; i < MAX_TUBES * 2; i += 2)
	{
		tubes[i].rec.x = tubesPos[i / 2].x;
		tubes[i].rec.y = tubesPos[i / 2].y;
		tubes[i].rec.width = TUBES_WIDTH;
		tubes[i].rec.height = 255;

		tubes[i + 1].rec.x = tubesPos[i / 2].x;
		tubes[i + 1].rec.y = 600 + tubesPos[i / 2].y - 255;
		tubes[i + 1].rec.width = TUBES_WIDTH;
		tubes[i + 1].rec.height = 255;

		tubes[i / 2].active = true;
	}

	score = 0;

	gameOver = false;
	gamePaused = false;
}


void Flappy::EvalCurFrame()
{
	if (gameOver)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			Start();
			gameOver = false;
		}
		return;
	}


	if (IsKeyPressed('P'))
		gamePaused = !gamePaused;



	if (gamePaused) return;


	// move the tubes with the same speed
	for (int i = 0; i < MAX_TUBES; i++)
		tubesPos[i].x -= tubesSpeedX;


	for (int i = 0; i < MAX_TUBES * 2; i += 2)
	{
		tubes[i].rec.x = tubesPos[i / 2].x;
		tubes[i + 1].rec.x = tubesPos[i / 2].x;
	}

	// push up when pressing the Space
	if (IsKeyDown(KEY_SPACE)) 
		floppy.position.y -= 3;
	else // otherwise keep falling
		floppy.position.y += 1;


	// Check Collisions
	for (int i = 0; i < MAX_TUBES * 2; i++)
	{
		if (CheckCollisionCircleRec(floppy.position, floppy.radius, tubes[i].rec))
		{
			gameOver = true;
			gamePaused = false;
		}
		else if ((tubesPos[i / 2].x < floppy.position.x) && tubes[i / 2].active && !gameOver)
		{
			score += 100;
			tubes[i / 2].active = false;

			if (score > hiScore) 
				hiScore = score;
		}
	}
}

// Draw game (one frame)
void Flappy::DrawCurFrame()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (!gameOver)
	{
		// Draw Ball
		DrawCircle(floppy.position.x, 
				   floppy.position.y,
				   floppy.radius, 
				   DARKGRAY);

		// Draw tubes
		for (int i = 0; i < MAX_TUBES; i++)
		{
			DrawRectangle(tubes[i * 2].rec.x,
						  tubes[i * 2].rec.y, 
						  tubes[i * 2].rec.width, 
						  tubes[i * 2].rec.height, 
						  GRAY);

			DrawRectangle(tubes[i * 2 + 1].rec.x, 
						  tubes[i * 2 + 1].rec.y,
						  tubes[i * 2 + 1].rec.width, 
						  tubes[i * 2 + 1].rec.height,
						  GRAY);
		}

		// Draw Scores
		DrawText(TextFormat("%04i", score), 20, 20, 40, GRAY);
		DrawText(TextFormat("HI-SCORE: %04i", hiScore), 20, 70, 20, LIGHTGRAY);

		if (gamePaused) 
			DrawText("Press P to Unpause", 
					 screenWidth / 2 - MeasureText("Press P to Unpause", 40) / 2,
					 screenHeight / 2 - 40, 40,
					 GRAY);
	}
	else
		DrawText("PRESS [ENTER] TO PLAY AGAIN", 
				 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, 
				 GetScreenHeight() / 2 - 50, 
				 20, 
				 GRAY);

	EndDrawing();
}


void Flappy::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}
