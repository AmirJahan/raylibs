#include <raylib.h>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
#define TILE_SIZE 77

    static const int screenW = 800;
    static const int screenH = 600;

    Vector2 borderGap = { screenW % TILE_SIZE, screenH % TILE_SIZE };
    int tailCount = 1;

    typedef struct Piece
    {
        Vector2 position;
        Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
        Color color;

        void Draw()
        {
            DrawRectangleV(position, size, color);
        }
    } Piece;



    Vector2 speed = Vector2{ TILE_SIZE, 0 };
    std::vector<Piece> player;



    bool gamePaused = false;
    bool canMove = false; // used so that the snake doesn't go back on the X or Y
    int frameCount = 0; // this is counter of when not paused
    bool gameOver = false;

    typedef struct Pickup
    {
        Vector2 position;
        Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
        bool active = false; // default is inactive, so it gets spawned to a random loc
        Color color = SKYBLUE;

        void newRandomLoc(Vector2 gap)
        {
            position = Vector2{ GetRandomValue(0, (screenW / TILE_SIZE) - 1) * TILE_SIZE + gap.x / 2, 
                GetRandomValue(0, (screenH / TILE_SIZE) - 1) * TILE_SIZE + gap.y / 2 };
        }

        void Draw()
        {
            DrawRectangleV(position, size, color);
        }

    } Pickup;
    Pickup pickup = { 0 };

    void Main();
    void Start();
    void Restart();
    void EvalCurFrame();
    void Interaction();
    void DrawCurFrame();
    void Update();
};

#endif