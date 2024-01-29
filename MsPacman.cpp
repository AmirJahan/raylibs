#include <raylib.h>
#include <vector>

#include "MsPacman.h"



void MsPacman::Main()
{
    InitWindow(600, 600, "Ms Pacman");

    Start();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Update();
    }

    CloseWindow();
}

void MsPacman::Start()
{
   center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void MsPacman::EvalCurFrame()
{
}

void MsPacman::DrawCurFrame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);


    DrawCircleSector(center, 
                     outerRadius,
                     abs (sin (GetTime())) * 45,
                     360 - abs(sin(GetTime())) * 45,
                     (int)segments, 
                     Fade(MAROON, 0.3f));

    EndDrawing();

}

void MsPacman::Update()
{
    EvalCurFrame();
    DrawCurFrame();
}
