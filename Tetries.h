#include <vector>
#include <raylib.h>

#pragma once


#ifndef TETRIES_H
#define TETRIES_H


using namespace std;

class Tetries
{
public:
#define SQUARE_SIZE 20
#define COLS 12
#define ROWS 20

	int screenWidth = 400;
	int screenHeight = 400;

	enum Status { EMPTY, BLOCKED, MOVING, CORNER }; // There might be other ones

	struct Tile
	{
		Vector2 pos;

		Status status = EMPTY;

		void Draw(bool itsThePiece)
		{
			if (status == EMPTY && !itsThePiece)
				DrawRectangleLines(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);
			else if (status == BLOCKED)
				DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
			else if (status == MOVING)
				DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, GRAY);
			else if (status == CORNER)
				DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, RED);
		}
	};

	struct Piece
	{
		// Grid R and Grid C
		int gridR, gridC;

		Vector2 position;
		vector<vector<Tile>> boxes; // # ROWS rows of # COLS tiles

		Piece() {}

		// this is only for the incoming piece
		Piece(Vector2 pos) : Piece()
		{
			this->position = pos;

			for (int r = 0; r < 4; r++)
			{
				vector<Tile> rowTiles;

				for (int c = 0; c < 4; c++)
				{
					// for each, let's make a tile
					Tile tile;
					tile.pos.x = position.x + c * SQUARE_SIZE;
					tile.pos.y = position.y + r * SQUARE_SIZE;

					rowTiles.push_back(tile);
				}

				boxes.push_back(rowTiles);
			}
		}


		void EmptyAll()
		{
			for (auto& row : boxes)
				for (auto& tile : row)
					tile.status = EMPTY;
		}

		void RandomPiece()
		{
			EmptyAll();

			boxes[0][0].status = CORNER;

			switch (GetRandomValue(0, 6))
			{
				case 0: // RECTA
					{
						boxes[0][1].status = MOVING;
						boxes[1][1].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[3][1].status = MOVING;
					}
					break;
				case 1: // CUBE
					{
						boxes[1][1].status = MOVING;
						boxes[1][2].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[2][2].status = MOVING;
					}
					break;

				case 2: // L INVERSE
					{
						boxes[0][1].status = MOVING;
						boxes[1][1].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[2][2].status = MOVING;
					}
					break;

				case 3: // L
					{
						boxes[0][1].status = MOVING;
						boxes[1][1].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[2][0].status = MOVING;
					}
					break;

				case 4: // CREU TALLADA
					{
						boxes[1][0].status = MOVING;
						boxes[1][1].status = MOVING;
						boxes[1][2].status = MOVING;
						boxes[2][1].status = MOVING;
					}
					break;

				case 5: // S
					{
						boxes[1][1].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[2][2].status = MOVING;
						boxes[3][2].status = MOVING;
					}
					break;
				case 6: // S INVERSE
					{
						boxes[1][2].status = MOVING;
						boxes[2][2].status = MOVING;
						boxes[2][1].status = MOVING;
						boxes[3][1].status = MOVING;
					}
					break;
				default:
					break;
			}


		}

		void Draw(bool itsThePiece)
		{
			for (auto& row : boxes)
				for (auto& tile : row)
					tile.Draw(itsThePiece);
		}

		void MoveLeft() { gridC--; SetPosition(); }
		void MoveRight() { gridC++; SetPosition(); }
		void MoveDown() { gridR++; SetPosition(); }



		void SetPosition()
		{
			float curPieceX = gridC * SQUARE_SIZE;
			float curPieceY = gridR * SQUARE_SIZE;

			this->position = Vector2{ curPieceX, curPieceY };

			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					boxes[r][c].pos.x = position.x + c * SQUARE_SIZE;
					boxes[r][c].pos.y = position.y + r * SQUARE_SIZE;
				}
			}
		}
	};


	int frameCounter;

	Piece incoming;
	Piece curPiece;

	vector<vector<Tile>> tiles; // # ROWS rows of # COLS tiles

	void Main();
	void Start();
	void EvalCurFrame();
	void DrawCurFrame();

	void InitializePiece();

	// Module Functions
	bool CanMove(int l, int d);
	void PlacePiece();
	void Turn();
};







#endif // !TETRIES_H
