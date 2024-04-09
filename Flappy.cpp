#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Flappy.h"
#include <algorithm>
#include <vector>



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
	columns.clear();
	player.position = Vector2{ 80, (float)screenHeight / 2 - player.radius };

	for (int i = 0; i < 3; i++)
	{
		float x = (float)(280 * i) + 200; // 200 initial offset

		float topHeight = (float)GetRandomValue(200, 300);

		Column column = Column{ x, topHeight };

		columns.push_back(column);
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
			Start();

		return;
	}

	if (IsKeyPressed('P'))
		gamePaused = !gamePaused;
	if (gamePaused) return;



	for (unsigned int i = 0; i < columns.size(); i++)
	{
		columns[i].Move();

		if (columns[i].CheckCollisionWithPlayer(player))
		{
			gameOver = true;
			gamePaused = false;
			return;
		}


		if (columns[i].PlayerCrossed(player) && !columns[i].gained)
		{
			columns[i].gained = true;
			score += 1;
			columns[i].color = RED;


			if (score > hiScore)
				hiScore = score;
		}

		if (columns[i].OutOfBounds())
		{
			columns[i].x = columns[columns.size() - 1].x + 280;
			columns[i].heightTop = (float)GetRandomValue(200, 300);
			columns[i].gained = false;

			// shuffle index of this column in the array
			// this part is somehwat unnecessary
			std::rotate(columns.begin() + i, columns.begin() + i + 1, columns.end());
		}
	}

	player.Move();

}

// Draw game (one frame)
void Flappy::DrawCurFrame()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (gameOver)
	{
		DrawText("PRESS [ENTER] TO PLAY AGAIN",
				 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
				 GetScreenHeight() / 2 - 50,
				 20,
				 GRAY);
	}
	else
	{
		// Draw Player
		player.Draw();


		for (unsigned int i = 0; i < columns.size(); i++)
			columns[i].Draw();



		// Draw Scores
		DrawText(TextFormat("%04i", score), 20, 20, 40, BLUE);
		DrawText(TextFormat("HI-SCORE: %04i", hiScore), 20, 70, 20, DARKBLUE);

		if (gamePaused)
			DrawText("Press P to Unpause",
					 screenWidth / 2 - MeasureText("Press P to Unpause", 40) / 2,
					 screenHeight / 2 - 40, 40,
					 GRAY);
	}

	EndDrawing();
}


void Flappy::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}
