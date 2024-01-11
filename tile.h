#pragma once
#ifndef TILE_H
#define TILE_H

#include "raylib.h"
// Include the string library
#include <string>

#include "tileStatus.h"



class Tile
{

public:
	Tile(int h, int v, int tileSize, int gridSize, int num);

	Rectangle rect;
	Vector2 textOrigin;

	std::string tileText;
	
	int fontSize = 50;
	int tileNum;

	tileStatus status = Hidden;

	void Display();
};

#endif
