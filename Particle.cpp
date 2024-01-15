#include <raylib.h>

#include <vector>

#include <math.h>

#include <iostream>
#include <ostream>
// update the center of the circle
#include <algorithm>


#include "Particle.h"

#include "Extensions.h"





void Particle::Main()
{

	// add an array of Circle objects with std::vector
	std::vector<Circle> circles;

	InitWindow(800, 800, "Particle Game");



	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		
		EvalCurFrame();

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawCurFrame();

		EndDrawing();
	}

	CloseWindow();
}

void Particle::Start()
{
}

void Particle::EvalCurFrame()
{
	Vector2 mousePoint = { 0.0f, 0.0f }; // for caching

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		mousePoint = GetMousePosition();

		int rateRange = rand() % 10;
		int fixedRate = 10;
		int rate = fixedRate + rateRange;

		for (int i = 0; i < rate; i++) // this is rate
		{
			Circle Circle = {
				mousePoint,
				(float) (rand() % 3 + 1),
				RandomColor(),
				(float)(rand() % 20 + 1), // speed
				(float)(rand() % 360) };

			circles.push_back(Circle);
		}
	}
}

void Particle::DrawCurFrame()
{
	// for each circle draw it
	for (int i = 0; i < circles.size(); i++)
	{
		if (circles[i].alive)
		{
			circles[i].update();
			circles[i].draw();
		}
		else
			circles.erase(circles.begin() + i);
	}
}

void Particle::Update()
{
	DrawCurFrame();
}



