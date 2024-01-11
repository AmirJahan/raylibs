#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "WallBreaker.h"



void WallBreaker::Main()
{
	InitWindow(screenWidth, screenHeight, "classic game: arkanoid");

	Start();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();
	}

	CloseWindow();
}


// Initialize game variables
void WallBreaker::Start()
{


	float spaceForBricks = screenWidth - (BRICKS_PER_ROW * GAP + GAP); // one extra gap at the end
	brickSize = Vector2{ spaceForBricks / BRICKS_PER_ROW, 24 };

	// Initialize player
	player.position = Vector2{ screenWidth / 2, screenHeight * 7 / 8 };
	player.size = Vector2{ screenWidth / 10, 20 };
	player.curLife = MAX_LIVES;

	// Initialize ball
	ball.position = Vector2{ screenWidth / 2, screenHeight * 7 / 8 - 30 };
	ball.speed = Vector2{ 0, 0 };
	ball.radius = 7;
	ball.active = false;



	// Initialize bricks


	for (int i = 0; i < ROWS_OF_BRICKS; i++)
	{
		for (int j = 0; j < BRICKS_PER_ROW; j++)
		{
			brick[i][j].origin = Vector2
			{
				GAP + j * (GAP + brickSize.x),
				GAP + i * (GAP + brickSize.y) 
			};

			brick[i][j].color = colors[i];
			brick[i][j].active = true;
		}
	}
}

// Update game (each frame)
void WallBreaker::EvalCurFrame()
{
	if (gameOver)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			Start();
			gameOver = false;
		}

		return; // if game is over, no need to continue any further inthis frame
	}

	if (gamePaused)
		return; // if game is paused, no need to continue any further inthis frame



	// MAIN LOOP
	// we get here, if game is not over
	if (IsKeyPressed('P')) gamePaused = !gamePaused;


	// Player movement logic
	if (IsKeyDown(KEY_LEFT)) player.position.x -= 5; // move left

	// when we reach far left
	if ((player.position.x - player.size.x / 2) <= 0) player.position.x = player.size.x / 2;

	if (IsKeyDown(KEY_RIGHT)) player.position.x += 5; // move right

	// when we reach far right
	if ((player.position.x + player.size.x / 2) >= screenWidth) player.position.x = screenWidth - player.size.x / 2;

	// Ball launching logic
	if (!ball.active)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			ball.active = true;
			ball.speed = Vector2{ 0, -5 };
		}
	}

	// Ball movement logic
	if (ball.active)
	{
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;
	}
	else
	{ // when ball gets de-activated
		ball.position = Vector2{ player.position.x, screenHeight * 7 / 8 - 20 };
	}

	// Collision logic: ball vs walls
	if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0)) ball.speed.x *= -1;
	if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;
	if ((ball.position.y + ball.radius) >= screenHeight)
	{
		// we have fallen to the death zone
		ball.speed = Vector2{ 0, 0 };
		ball.active = false;

		player.curLife--; // we lost life
	}

	// Collision logic: ball vs player



	if (CheckCollisionCircleRec(ball.position, ball.radius, PlayersCurrentRect()))
	{
		if (ball.speed.y > 0) // if going down
		{
			ball.speed.y *= -1; // when hit the player go up

			// give it an x in the opposite diretion of where the player is
			ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 2) * 5;
		}
	}

	// Collision logic: ball vs bricks
	for (int i = 0; i < ROWS_OF_BRICKS; i++)
	{
		for (int j = 0; j < BRICKS_PER_ROW; j++)
		{
			if (brick[i][j].active)
			{
				// Hit below
				if (((ball.position.y - ball.radius) <= (brick[i][j].origin.y + brickSize.y / 2)) &&
					((ball.position.y - ball.radius) > (brick[i][j].origin.y + brickSize.y / 2 + ball.speed.y)) &&
					((fabs(ball.position.x - brick[i][j].origin.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y < 0))
				{
					brick[i][j].active = false;
					ball.speed.y *= -1;
				}
				// Hit above
				else if (((ball.position.y + ball.radius) >= (brick[i][j].origin.y - brickSize.y / 2)) &&
						 ((ball.position.y + ball.radius) < (brick[i][j].origin.y - brickSize.y / 2 + ball.speed.y)) &&
						 ((fabs(ball.position.x - brick[i][j].origin.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y > 0))
				{
					brick[i][j].active = false;
					ball.speed.y *= -1;
				}
				// Hit left
				else if (((ball.position.x + ball.radius) >= (brick[i][j].origin.x - brickSize.x / 2)) &&
						 ((ball.position.x + ball.radius) < (brick[i][j].origin.x - brickSize.x / 2 + ball.speed.x)) &&
						 ((fabs(ball.position.y - brick[i][j].origin.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x > 0))
				{
					brick[i][j].active = false;
					ball.speed.x *= -1;
				}
				// Hit right
				else if (((ball.position.x - ball.radius) <= (brick[i][j].origin.x + brickSize.x / 2)) &&
						 ((ball.position.x - ball.radius) > (brick[i][j].origin.x + brickSize.x / 2 + ball.speed.x)) &&
						 ((fabs(ball.position.y - brick[i][j].origin.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x < 0))
				{
					brick[i][j].active = false;
					ball.speed.x *= -1;
				}
			}
		}
	}

	// Game is over unless there is at least one active brick or life
	gameOver = true;

	if (player.curLife > 0)
	{
		for (int i = 0; i < ROWS_OF_BRICKS; i++)
		{
			for (int j = 0; j < BRICKS_PER_ROW; j++)
			{
				if (brick[i][j].active)
				{
					gameOver = false;
					return; // there's at least one active, no need to continue
				}
			}
		}
	}
}


Rectangle WallBreaker::PlayersCurrentRect()
{
	// get player's current BB
	return Rectangle{
						player.position.x - player.size.x / 2,
						player.position.y - player.size.y / 2,
						player.size.x,
						player.size.y
	};
}

// Draw game (one frame)
void WallBreaker::DrawCurFrame()
{
	BeginDrawing();

	ClearBackground(BLACK);

	if (!gameOver)
	{
		// Draw player bar
		Rectangle playerRect = PlayersCurrentRect();

		DrawRectangleRounded(playerRect, 6, 8, GREEN);


		// Draw player lives
		for (int i = 0; i < player.curLife; i++)
			DrawRectangle(20 + 40 * i,
						  screenHeight - 30,
						  35,
						  10,
						  LIGHTGRAY);

		// Draw ball
		DrawCircleV(ball.position,
					ball.radius,
					MAROON);

		// Draw bricks
		for (int i = 0; i < ROWS_OF_BRICKS; i++)
		{
			for (int j = 0; j < BRICKS_PER_ROW; j++)
			{
				if (brick[i][j].active)
				{
					Rectangle rect = Rectangle{ brick[i][j].origin.x,
								  brick[i][j].origin.y,
								  brickSize.x,
								  brickSize.y };

					DrawRectangleRounded(rect, 
										 4, 
										 8,
										 brick[i][j].color);

				}
			}

			if (gamePaused)
				DrawText("GAME PAUSED",
						 screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2,
						 screenHeight / 2 - 40, 40,
						 GRAY);
		}
	}
	else
		DrawText("PRESS [ENTER] TO PLAY AGAIN",
				 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
				 GetScreenHeight() / 2 - 50,
				 20,
				 GRAY);

	EndDrawing();
	}

	// Update and Draw (one frame)
	void WallBreaker::Update()
	{
		EvalCurFrame();
		DrawCurFrame();
	}



