#pragma once

#include "raylib.h"
#include <vector>
#include <string>

#include "tile.h"



#ifndef WALL_H
#define WALL_H



class WallBreaker 
{
public:

    //----------------------------------------------------------------------------------
    // Some Defines
    //----------------------------------------------------------------------------------
#define MAX_LIVES         5
#define ROWS_OF_BRICKS         5
#define BRICKS_PER_ROW        12
#define GAP 8

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
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
    } Brick;

    //------------------------------------------------------------------------------------
    // Global Variables Declaration
    //------------------------------------------------------------------------------------
    static const int screenWidth = 800;
    static const int screenHeight = 450;

    bool gameOver = false;
    bool gamePaused = false;

    // we have one color per row
    Color colors[ROWS_OF_BRICKS] = { PURPLE, BLUE, GOLD, PINK, YELLOW };

    Player player = { 0 };
    Ball ball = { 0 };
    Brick brick[ROWS_OF_BRICKS][BRICKS_PER_ROW] = { 0 };
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