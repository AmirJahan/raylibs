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
    InitWindow(screenW, screenH, "classic game: snake");
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
    Piece head_1;
    head_1.color = DARKBLUE;
    head_1.position = Vector2{ borderGap.x / 2, borderGap.y / 2 };
    player.push_back(head_1);
}

void Snake::Restart()
{
    frameCount = 0;
    gameOver = false;
    gamePaused = false;

    canMove = false;

    player.clear();

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
                for (int i = player.size() - 1; i > 0; i--)
                    player[i].position = player[i - 1].position;


                player[0].position += speed;
                canMove = true;
            }

            // Game over upon collision with the walls
            if (((player[0].position.x) > (screenW - borderGap.x)) ||
                ((player[0].position.y) > (screenH - borderGap.y)) ||
                (player[0].position.x < 0) ||
                (player[0].position.y < 0))
            {
                gameOver = true;
            }

            // if pick up is not active, let's spawn one
            if (!pickup.active)
            {
                pickup.active = true;
                pickup.newRandomLoc(borderGap);

                for (int i = 0; i < player.size(); i++)
                {
                    while (pickup.position == player[i].position)
                    {
                        pickup.newRandomLoc(borderGap);
                        i = 0; // redo
                    }
                }
            }

            // collision with the pickup
            if (player[0].position == pickup.position)
            {
                Piece newHead;
                newHead.color = BLUE;
                // no need to set the position. As soon as we pass, this new one
                // will be added to the end of the tail
                player.push_back(newHead);
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
            speed = Vector2{ TILE_SIZE, 0 };
            canMove = false;
        }
    }

    if (IsKeyPressed(KEY_LEFT) && speed.x == 0 && canMove)
    {
        speed = Vector2{ -TILE_SIZE, 0 };
        canMove = false;
    }

    if (IsKeyPressed(KEY_UP) && speed.y == 0 && canMove)
    {
        speed = Vector2{ 0, -TILE_SIZE };
        canMove = false;
    }

    if (IsKeyPressed(KEY_DOWN) && speed.y == 0 && canMove)
    {
        speed = Vector2{ 0, TILE_SIZE };
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
        for (int i = 0; i < screenW / TILE_SIZE + 1; i++)
        {
            Vector2 start = { TILE_SIZE * i + borderGap.x / 2, borderGap.y / 2 };
            Vector2 end = { TILE_SIZE * i + borderGap.x / 2, screenH - borderGap.y / 2 };

            DrawLineV(start, end, LIGHTGRAY);
        }

        for (int i = 0; i < screenH / TILE_SIZE + 1; i++)
        {
            Vector2 start = Vector2 { borderGap.x / 2, TILE_SIZE * i + borderGap.y / 2 };
            Vector2 end = Vector2 { screenW - borderGap.x / 2, TILE_SIZE * i + borderGap.y / 2 };

            DrawLineV(start,
                      end, LIGHTGRAY);
        }


        for (Piece head : player)
            head.Draw();

        // Draw pickup
        pickup.Draw();

        if (gamePaused)
            DrawText("GAME PAUSED", screenW / 2 - MeasureText("GAME PAUSED", 40) / 2, screenH / 2 - 40, 40, GRAY);
    }
    else // game over
        DrawText("PRESS [ENTER] TO PLAY AGAIN", 
                 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, 
                 GetScreenHeight() / 2 - 50, 20,
                 GRAY);

    EndDrawing();
}

void Snake::Update()
{
    EvalCurFrame();
    DrawCurFrame();
}
