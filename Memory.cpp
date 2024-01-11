#include "Memory.h"
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <random>     // For std::default_random_engine
#include "games.h"

#include <raymath.h>

#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>



void Memory::Main()
{
	InitWindow(screenWidth, screenHeight, "Memory Puzzle Game");

	Start();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();
		EndDrawing();
	}

	CloseWindow();
}

void Memory::Start()
{
	tilesArr.clear();

	int tileSize = (int)((screenHeight - GAP * (gridSize + 1)) / gridSize);   


	// produce an array of number from 0 to 8 twice
	for (int i = 0; i < gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i); // Assign values from 0 to 8
		numbers.push_back(i); // and again
	}

	for (int row = 0; row < gridSize; row++)
		for (int col = 0; col < gridSize; col++)
		{
			int randId = rand() % numbers.size();
			int thisNum = numbers[randId];
			Tile tile = Tile(row, col, tileSize, gridSize, thisNum);
			tilesArr.push_back(tile);
			numbers.erase(numbers.begin() + randId);
		}
}

void Memory::EvalCurFrame()
{
	Vector2 mousePoint = { 0.0f, 0.0f }; // for caching
	mousePoint = GetMousePosition();



	// while a compare is happening we shuldn't allow clicking
	if (!canClick)
		goto skipClickingLabel;


	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < tilesArr.size(); i++)
		{
			if (CheckCollisionPointRec(mousePoint, tilesArr[i].rect))
			{
				if (tilesArr[i].status == Hidden) // only when clicking on hidden tiles
				{
					// no matter what, do flip

					tilesArr[i].status = Flipped;

					if (tile_1_index == -1)
					{
						// this was the first click
						tile_1_index = i;
					}
					else
					{
						tile_2_index = i;
						timeOfSecondClick = GetTime(); // when did we click
						compareMode = true;
						canClick = false; // until compare is finished
					}
				}
			}
		}
	}


skipClickingLabel:

	if (compareMode) // we can compare
	{
		// only pause, if the are NOT the same, so that the player can see


		if (GetTime() > timeOfSecondClick + WAIT_TIME) // a second after second click
		{
			// Do compare
			if (tilesArr[tile_1_index].tileNum == tilesArr[tile_2_index].tileNum)
			{
				// match
				tilesArr[tile_1_index].status = Found;
				tilesArr[tile_2_index].status = Found;
			}
			else
			{
				// Not a match
				tilesArr[tile_1_index].status = Hidden;
				tilesArr[tile_2_index].status = Hidden;
			}

			compareMode = false;
			tile_1_index = -1;
			tile_2_index = -1;
			canClick = true;
		}
	}

}

void Memory::DrawCurFrame()
{

	for (Tile tile : tilesArr)
		tile.Display();




}

void Memory::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}