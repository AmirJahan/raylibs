#include "MemoryPuzzleGame.h"
#include <iostream>
#include <raylib.h>
#include <sstream>

#include "games.h"
#include <vector>

#include <raymath.h>



void MemoryPuzzleGame::test() 
{
	int width = 1080;
	int height = 720;
   
	InitWindow(width, height, "Memory Puzzle Game");

	SetTargetFPS(60);

	int gridSize = 4;
	float tileSize = height / gridSize; // Subtract 6 for the gap between each two  


	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground( RAYWHITE);

		for (int h = 0; h < 4; h++)
		{
			for (int v = 0; v < 4; v++)
			{
				Rectangle rect = Rectangle{  h * tileSize +5,
											 v * tileSize +5,
											tileSize - 10, tileSize -10 };
				DrawRectangleRounded(rect, 0.1, 12, BLACK);
			}
		}




		EndDrawing();
	}

	CloseWindow();

}
