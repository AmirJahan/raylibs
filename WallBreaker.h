#pragma once

#include "raylib.h"
#include <vector>
#include <string>

#include "tile.h"
#include <vector>


#ifndef WALL_H
#define WALL_H



class WallBreaker 
{
public:


#define MAX_LIVES         5
#define ROWS_OF_BRICKS         5
#define BRICKS_PER_ROW        12
#define GAP 2
#define BRICK_HEIGHT 24

// typedef ~ Alias
    typedef struct Player {
        Vector2 position;
        Vector2 size;
        int curLife;
    } Player;

    typedef struct Ball {
        Vector2 position;
        Vector2 speed;
        int radius;
        bool active;
    } Ball;

    typedef struct Brick {
        Vector2 origin;
        bool active;
        Color color;
        Rectangle rect;

        void DrawBrick()
        {
            DrawRectangleRounded(rect,
                                 0.5f,
                                 4,
                                 color);
        }

    } Brick;



    static const int screenWidth = 800;
    static const int screenHeight = 450;

    bool gameOver = false;
    bool gamePaused = false;

    // we have one color per row
    Color colors[ROWS_OF_BRICKS] = { PURPLE, BLUE, GOLD, PINK, YELLOW };

    Player player = { 0 };
    Ball ball = { 0 };

    std::vector<Brick> bricks;

    Vector2 brickSize = { 0 };



    //------------------------------------------------------------------------------------
    // Module Functions Declaration (local)
    //------------------------------------------------------------------------------------
    void Main();
    void Start();         // Initialize game
    void EvalCurFrame();       // Update game (one frame)
    void DrawCurFrame();         // Draw game (one frame)
    void Update();  // Update and Draw (one frame)
    Rectangle PlayersCurrentRect();
};


#endif