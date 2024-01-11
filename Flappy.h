#pragma once

#include "raylib.h"
#include <vector>
#include <string>

#include "tile.h"


#ifndef FLAPPY_H
#define FLAPPY_H



class Flappy
{
public: 

#define MAX_TUBES 100
#define BALL_RADIUS 16
#define TUBES_WIDTH 80

    typedef struct Floppy
    {
        Vector2 position;
        int radius;
        Color color;
    } Floppy;

    typedef struct Tubes
    {
        Rectangle rec;
        Color color;
        bool active;
    } Tubes;

    static const int screenWidth = 800;
    static const int screenHeight = 450;

    bool gameOver = false;
    bool gamePaused = false;
    int score = 0;
    int hiScore = 0;

    Floppy floppy = { 0 };
    Tubes tubes[MAX_TUBES * 2] = { 0 };
    Vector2 tubesPos[MAX_TUBES] = { 0 };
    int tubesSpeedX = 0;


    void Main();
    void Start();
    void EvalCurFrame();
    void DrawCurFrame();
    void Update();
};


#endif