#include "Tetries.h"
#include <raylib.h>
#include <vector>

using namespace std;

void Tetries::Main()
{
	InitWindow(screenWidth, screenHeight, "Tetires");

	Start();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		EvalCurFrame();  // OUR FUNCTION

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCurFrame(); // OUR FUNCTION
		EndDrawing();
	}

	CloseWindow();
}

void Tetries::Start()
{
	for (int r = 0; r < ROWS; r++)
	{
		vector<Tile> rowTiles;

		for (int c = 0; c < COLS; c++)
		{
			// for each, let's make a tile
			Tile tile;
			tile.pos.x = 0 + c * SQUARE_SIZE;
			tile.pos.y = 0 + r * SQUARE_SIZE;

			if (r == ROWS - 1 || c == 0 || c == COLS - 1)
				tile.status = BLOCKED;

			rowTiles.push_back(tile);
		}

		tiles.push_back(rowTiles);
	}

	float incomingX = COLS * SQUARE_SIZE + 50;
	float incomingY = 50;
	incoming = Piece(Vector2{ incomingX, incomingY });
	incoming.RandomPiece();
	InitializePiece();
	frameCounter = 0;

}

void Tetries::EvalCurFrame()
{
	frameCounter++;

	if (frameCounter % 50 == 0)
	{
		if (CanMove(0, 1))
			curPiece.MoveDown();
		else
		{
			PlacePiece();
			InitializePiece();
		}
	}

	if (IsKeyPressed(KEY_LEFT) && CanMove(-1, 0)) curPiece.MoveLeft();
	if (IsKeyPressed(KEY_RIGHT) && CanMove(1, 0)) curPiece.MoveRight();
	if (IsKeyPressed(KEY_UP))
		Turn();
}

void Tetries::DrawCurFrame()
{
	for (auto& row : tiles)
		for (auto& tile : row)
			tile.Draw(false);


	incoming.Draw(false);
	curPiece.Draw(true);
}

void Tetries::InitializePiece()
{
	float incomingX = COLS * SQUARE_SIZE + 50;
	float incomingY = 50;

	curPiece = incoming;
	curPiece.gridR = 0;
	curPiece.gridC = 4;

	incoming = Piece(Vector2{ incomingX, incomingY });
	incoming.RandomPiece();

	curPiece.SetPosition();

	frameCounter = 0;
}

void Tetries::PlacePiece()
{
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			if (curPiece.boxes[r][c].status == MOVING)
				tiles[r + curPiece.gridR][c + curPiece.gridC].status = BLOCKED;

}

void Tetries::Turn()
{
	// it takes the current piece and rotates it

	// A temp vector to store the data to be overriden
	Piece onePiece = curPiece;

	for (int r = 0;r < 4;r++)
		for (int c = 0; c < 4; c++)
		{
			onePiece.boxes[3 - c][r] = curPiece.boxes[r][c];
		}
	curPiece = onePiece;
}

bool Tetries::CanMove(int l, int d)
{
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			if (curPiece.boxes[r][c].status == MOVING)
				if (tiles[r + curPiece.gridR + d][c + curPiece.gridC + l].status == BLOCKED)
					return false;


	return true;
}
