#include "Tile.h"
#include "Memory.h"

#include <raylib.h>
#include <raymath.h>
#include <string>

#include <tuple>

using namespace std;


Tile::Tile(int h, int v, int tileSize, int gridSize, int num)
{
	rect = Rectangle{(float)h * (tileSize + GAP) + GAP,
					 (float)v * (tileSize + GAP) + GAP,
					 (float)tileSize,
					 (float)tileSize};


	Vector2 cen = Vector2{ 
		rect.x + rect.width / 2,
		rect.y + rect.height / 2 };

	tileNum = num;
	tileText = std::to_string(tileNum);


	int txtWidth = MeasureText(tileText.c_str(), fontSize);

	textOrigin = Vector2
	{
		cen.x - txtWidth / 2,
		cen.y - fontSize / 2
	};
}




void Tile::Display()
{
	switch (status)
	{
		case Hidden:
			DrawRectangleRounded(rect, 0.1f, 12, LIGHTGRAY);
			DrawText("?", textOrigin.x, textOrigin.y, fontSize, BLACK);
			break;
		case Flipped:
			DrawRectangleRounded(rect, 0.1f, 12, ORANGE);
			DrawText(tileText.c_str(), textOrigin.x, textOrigin.y, fontSize, BLACK);
			break;
		case Found:
			DrawRectangleRounded(rect, 0.1f, 12, GREEN);
			DrawText("F", textOrigin.x, textOrigin.y, fontSize, BLACK);
			break;
		default:
			break;
	}
}

