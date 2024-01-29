#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "WallBreaker.h"



//Mid-term assignment
/*
Develop CircleToRoundRectCollision
Depending on where the collision happens, have a direction calculated
Include unlimited number of levels that come up after another
Have new life drop downs
Have a cheat drow down (such as when the player catches the cheat, 
		for the next 5 seconds (with feedback), there won't be any speed reversal 
		with the bricks. So the ball can cut through many bricks at once
Include sound effects
Bonus: Find a way to play it on your phone

*/


void WallBreaker::Main()
{
	InitWindow(screenWidth, screenHeight, "Wall Breaker");

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
	brickSize = Vector2{ spaceForBricks / BRICKS_PER_ROW, BRICK_HEIGHT };



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
			float x = GAP + j * (GAP + brickSize.x);
			float y = GAP + i * (GAP + brickSize.y);

			Brick b = Brick{ Vector2 { x, y	} ,
				true, colors[i],
				Rectangle{ x, y, brickSize.x, brickSize.y } };

			bricks.push_back(b);
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



	// MAIN LOOP
	// we get here, if game is not over
	if (IsKeyPressed('P')) gamePaused = !gamePaused;

	if (gamePaused)
		return; // if game is paused, no need to continue any further inthis frame


	// Player movement logic
	if (IsKeyDown(KEY_LEFT)) player.position.x -= 5; // move left

	// when we reach far left
	if ((player.position.x - player.size.x / 2) <= 0) player.position.x = player.size.x / 2;

	if (IsKeyDown(KEY_RIGHT)) player.position.x += 5; // move right

	// when we reach far right
	if ((player.position.x + player.size.x / 2) >= screenWidth)
		player.position.x = screenWidth - player.size.x / 2;

	// Ball launching logic
	if (!ball.active)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			ball.active = true;
			ball.speed = Vector2{ 0, -5}; // go upwards
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
		// put it on top of the player
		ball.position = Vector2{ player.position.x, screenHeight * 7 / 8 - 20 };
	}

	// Collision logic: ball vs walls
	if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0))
		ball.speed.x *= -1; // running to vertical walla
	if ((ball.position.y - ball.radius) <= 0) 
		ball.speed.y *= -1; // running to the top wall
	if ((ball.position.y + ball.radius) >= screenHeight)
	{
		// we have fallen to the death zone
		ball.speed = Vector2{ 0, 0 };
		ball.active = false;

		player.curLife--; // we lost life
	}

	// Collision logic: ball vs player
#pragma region ball_player cllision

	if (CheckCollisionCircleRec(ball.position, ball.radius, PlayersCurrentRect()))
	{
		if (ball.speed.y > 0) // if going down
		{
			ball.speed.y *= -1; // when hit the player go up

			// give it an x in the opposite diretion of where the player is
			ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 2) * 5;
		}
	}
#pragma endregion ball_player cllision



	for (int i = 0; i < bricks.size(); i++)
	{
		if (CheckCollisionCircleRec(ball.position, ball.radius, bricks[i].rect))
		{

			bricks.erase(bricks.begin() + i);
			ball.speed.y *= -1;
			break; // if one brick collision happened. Let's break
			// so, we don't collilde with two bricks in the same frame
		}
	}

	if (player.curLife > 0)
	{
		for (Brick b : bricks)
			if (b.active)
				gameOver = false;
			else
				gameOver = true;
	}
	else
		gameOver = true;
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

		DrawRectangleRounded(playerRect, 4, 8, GREEN);

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

		for (Brick b : bricks)
		{
			b.DrawBrick();
		}

			if (gamePaused)
				DrawText("GAME PAUSED",
						 screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2,
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

	// Update and Draw (one frame)
	void WallBreaker::Update()
	{
		EvalCurFrame();
		DrawCurFrame();
	}



