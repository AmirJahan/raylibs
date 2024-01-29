#pragma once

#include "raylib.h"
#include <vector>
#include <string>




#ifndef MSPACMAN_H
#define MSPACMAN_H



class MsPacman
{

public:

    const int screenWidth = 800;
    const int screenHeight = 450;

    Vector2 center;

    float outerRadius = 180.0f;
    float startAngle = 0.0f;
    float endAngle = 180.0f;
    float segments = 10.0f;
    float minSegments = 4;



    void Main();
    void Start();         // Initialize game
    void EvalCurFrame();       // Update game (one frame)
    void DrawCurFrame();         // Draw game (one frame)
    void Update();  // Update and Draw (one frame)

};


#endif





