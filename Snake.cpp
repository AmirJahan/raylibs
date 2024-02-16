#include "Snake.h"
#include "raylib.h"
#include <iostream>
#include <ostream>

// add new function for += to Vector2
Vector2& operator+=(Vector2& a, const Vector2& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

// add new function for == to Vector2
bool operator==(const Vector2& a, const Vector2& b)
{
    return a.x == b.x && a.y == b.y;
}

// implement all methods from header file
void Snake::Main()
{
    InitWindow(screenWidth, screenHeight, "classic game: snake");
    Start();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        Update();
    }

    CloseWindow();
}

void Snake::Start()
{
    Head head_1;
    head_1.color = DARKBLUE;
    head_1.position = Vector2{ borderGap.x / 2, borderGap.y / 2 };
    heads.push_back(head_1);
}

void Snake::Restart()
{
    frameCount = 0;
    gameOver = false;
    gamePaused = false;

    canMove = false;

    heads.clear();

    Start();
}

void Snake::EvalCurFrame()
{
    if (!gameOver)
    {
        if (IsKeyPressed('P'))
            gamePaused = !gamePaused;

        if (!gamePaused)
        {
            frameCount++;

            Interaction();

            if (frameCount % 20 == 0)
            {
                // from the back
                for (int i = heads.size() - 1; i > 0; i--)
                    heads[i].position = heads[i - 1].position;


                heads[0].position += speed;
                canMove = true;
            }

            // Game over upon collision with the walls
            if (((heads[0].position.x) > (screenWidth - borderGap.x)) ||
                ((heads[0].position.y) > (screenHeight - borderGap.y)) ||
                (heads[0].position.x < 0) ||
                (heads[0].position.y < 0))
            {
                gameOver = true;
            }

            // if pick up is not active, let's spawn one
            if (!pickup.active)
            {
                pickup.active = true;
                pickup.newRandomLoc(borderGap);

                for (int i = 0; i < heads.size(); i++)
                {
                    while (pickup.position == heads[i].position)
                    {
                        pickup.newRandomLoc(borderGap);
                        i = 0; // redo
                    }
                }
            }

            if (heads[0].position == pickup.position)
            {
                Head newHead;
                newHead.color = BLUE;

                newHead.position = Vector2{ pickup.position.x, pickup.position.y }; // deep copy
                heads.push_back(newHead);
                pickup.active = false;
            }
        }
    }
    else // game is over
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            Restart();
            gameOver = false;
        }
    }
}

void Snake::Interaction()
{
    // Player control
    if (IsKeyPressed(KEY_RIGHT))
    {
        if (speed.x == 0 && canMove)
        {
            speed = Vector2{ SQUARE_SIZE, 0 };
            canMove = false;
        }
    }

    if (IsKeyPressed(KEY_LEFT) && speed.x == 0 && canMove)
    {
        speed = Vector2{ -SQUARE_SIZE, 0 };
        canMove = false;
    }

    if (IsKeyPressed(KEY_UP) && speed.y == 0 && canMove)
    {
        speed = Vector2{ 0, -SQUARE_SIZE };
        canMove = false;
    }

    if (IsKeyPressed(KEY_DOWN) && speed.y == 0 && canMove)
    {
        speed = Vector2{ 0, SQUARE_SIZE };
        canMove = false;
    }
}

void Snake::DrawCurFrame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        // Draw grid lines
        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            Vector2 start = { SQUARE_SIZE * i + borderGap.x / 2, borderGap.y / 2 };
            Vector2 end = { SQUARE_SIZE * i + borderGap.x / 2, screenHeight - borderGap.y / 2 };

            DrawLineV(start, end, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV(Vector2{ borderGap.x / 2, SQUARE_SIZE * i + borderGap.y / 2 }, Vector2{ screenWidth - borderGap.x / 2, SQUARE_SIZE * i + borderGap.y / 2 }, LIGHTGRAY);
        }


        for (Head head : heads)
            head.Draw();

        // Draw pickup
        pickup.Draw();

        if (gamePaused)
            DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else // game over
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();
}

void Snake::Update()
{
    EvalCurFrame();
    DrawCurFrame();
}
