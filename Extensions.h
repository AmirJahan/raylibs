#include <raylib.h>

#include <vector>

#include <math.h>

#include <iostream>
#include <ostream>
// update the center of the circle
#include <algorithm>


// test.h
#ifndef EXTENSIONS_H
#define EXTENSIONS_H



struct Circle
{
    Vector2 center;
    float radius;
    Color color;
    float speed;
    float direction; // this is the angle
    bool alive = true;
    float gravity = 10;

    // add a constructor with all arguments
    Circle(Vector2 center, float radius, Color color, float speed, float direction)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
        this->speed = speed;
        this->direction = direction;
        alive = true;
    }

    // add a new function to evaluate circle
    void update()
    {

        // ...

        // don't let speed get below 1
        center.x += cos(direction * DEG2RAD) * std::max(speed, 1.0f);
        center.y += sin(direction * DEG2RAD) * std::max(speed, 1.0f) + gravity;

        // fade color's alpha channel gradually
        if (color.a >= 1)
            color.a -= 1; // this is decay rate
        else
            alive = false;

        // enlarge the radius by 1
        radius += 0.1f;

        // initial speed continually dies
        speed -= 1;
    }

    void draw()
    {
        DrawCircleV(center, radius, color);
    }
};




Color RandomColor();

#endif
