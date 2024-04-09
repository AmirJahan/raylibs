#pragma once

#include "raylib.h"
#include <vector>
#include <string>



#ifndef FLAPPY_H
#define FLAPPY_H



class Flappy
{
public:

    struct Player
    {
        Vector2 position;
        int radius = 20;
        Color color = BLACK;

        void Draw()
        {
            DrawCircle(position.x,
                       position.y,
                       radius,
                       color);
        }

        void Move()
        {
            // push up when pressing the Space
            if (IsKeyDown(KEY_SPACE))
                position.y -= 3;
            else // otherwise keep falling
                position.y += 1;
        }
    };





    struct Column
    {
        float x;
        float width = 80;
        float heightTop;
        float heightBottom;

        Color color = GRAY;
        bool gained = false;

        float yBottom;

        // constructor with all arguments
        Column(float x, float heightTop)
        {
            this->x = x;
            this->heightTop = heightTop;
            this->yBottom = heightTop + 100;
            this->heightBottom = screenHeight - yBottom;
        }


        void Move()
        {
            x -= 1;
        }

        Rectangle topRect()
        {
            return Rectangle{ x, 0, width, heightTop };
        }

        Rectangle bottomRect()
        {
            return Rectangle{ x, yBottom, width, heightBottom };
        }

        void Draw()
        {

            // if within bounds, draw
            if (x + width > 0 && x < screenWidth)
            {
                DrawRectangleRec(topRect(), color);
                DrawRectangleRec(bottomRect(), color);
            }
        }

        bool CheckCollisionWithPlayer(Player player)
        {
            return CheckCollisionCircleRec(player.position, player.radius, topRect()) ||
                CheckCollisionCircleRec(player.position, player.radius, bottomRect());
        }




        bool PlayerCrossed(Player player)
        {
            return x + width < player.position.x;
        }

        bool OutOfBounds()
        {
            return x + width < 0;
        }
    };

    static const int screenWidth = 800;
    static const int screenHeight = 450;

    bool gameOver = false;
    bool gamePaused = false;
    int score = 0;
    int hiScore = 0;

    Player player = { 0 };
    std::vector<Column> columns;



    void Main();
    void Start();
    void EvalCurFrame();
    void DrawCurFrame();
    void Update();
};


#endif