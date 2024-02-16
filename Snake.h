#include <raylib.h>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
#define SQUARE_SIZE 77
#define MAX_TAIL_LENGTH 20

    static const int screenWidth = 800;
    static const int screenHeight = 600;

    Vector2 borderGap = { screenWidth % SQUARE_SIZE, screenHeight % SQUARE_SIZE };
    int tailCount = 1;

    typedef struct Head
    {
        Vector2 position;
        Vector2 size = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
        Color color;

        void Draw()
        {
            DrawRectangleV(position, size, color);
        }
    } Head;



    Vector2 speed = Vector2{ SQUARE_SIZE, 0 };
    std::vector<Head> heads;

    bool gamePaused = false;
    bool canMove = false; // used so that the snake doesn't go back on the X or Y
    int frameCount = 0; // this is counter of when not paused
    bool gameOver = false;

    typedef struct Pickup
    {
        Vector2 position;
        Vector2 size = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
        bool active = false; // default is inactive, so it gets spawned to a random loc
        Color color = SKYBLUE;

        void newRandomLoc(Vector2 gap)
        {
            position = Vector2{ GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + gap.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + gap.y / 2 };
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