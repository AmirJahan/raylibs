#include <raylib.h>
#include <vector>

#include "Spirograph.H"

#include "Extensions.h"




void Spirograph::drawCurve()
{
	// drawing line between two points
	if (pointsArr.size() < 3) // this is the first time
	{
		previousLoc = Vector2{ drawHeadX, drawHeadY };
		pointsArr.push_back(previousLoc);
	}
	else
	{
		// add the point to the array

		pointsArr.push_back(previousLoc);


		for (int i = 1; i < pointsArr.size(); i++)
		{
			Vector2 curP = pointsArr[i];
			Vector2 preP = pointsArr[i - 1];

			DrawLine (curP.x, curP.y, preP.x, preP.y, spiroColor);
		}
		previousLoc = Vector2{ drawHeadX, drawHeadY };
	}
}



void Spirograph::Main()
{
	Start();

	InitWindow(width, height, "Spirograph");
	SetTargetFPS(myFPS);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		Update();

		EndDrawing();
	}

	CloseWindow();
}


void Spirograph::Start()
{
	cenX = width / 2;
	cenY = height / 2;
	rotationRadius = outerRadius - drawRingRadius; // rotation ring radius calculated

	spiroColor = RandomColor();
}


void Spirograph::EvalCurFrame()
{
	if (IsKeyDown(KEY_UP))
	{
		drawRingRadius++;
		pointsArr.clear();
		spiroColor = RandomColor();

	} else 	if (IsKeyDown(KEY_DOWN))
	{
		drawRingRadius--;
		pointsArr.clear();
		spiroColor = RandomColor();

	} else if (IsKeyDown(KEY_LEFT))
	{
		drawHeadDistToCen--;
		pointsArr.clear();
		spiroColor = RandomColor();

	} else if (IsKeyDown(KEY_RIGHT))
	{
		drawHeadDistToCen++;
		pointsArr.clear();
		spiroColor = RandomColor();

	}
	else if (IsKeyDown(KEY_W))
	{
		speed += 0.1;
		pointsArr.clear();
		spiroColor = RandomColor();
	}
	else if (IsKeyDown(KEY_S))
	{
		speed -= 0.1;
		pointsArr.clear();
		spiroColor = RandomColor();
	}


	rotationRadius = outerRadius - drawRingRadius; // rotation ring radius calculated


	outerInnerRatio = outerRadius / (drawRingRadius - drawHeadDistToCen);


	// small ring
	drawHeadRingCenterX = cenX + sin(currentRotation * DEG2RAD) * rotationRadius ;
	drawHeadRingCenterY = cenY + cos(currentRotation * DEG2RAD) * rotationRadius ;


	// calculate head

		headCurDegree = currentRotation * outerInnerRatio;


	drawHeadX = drawHeadRingCenterX + sin(headCurDegree * DEG2RAD) * drawHeadDistToCen;
	drawHeadY = drawHeadRingCenterY + cos(headCurDegree * DEG2RAD) * drawHeadDistToCen;


	currentRotation += (speed * 3); // 3 is default in 120 fps


}
void Spirograph::DrawCurFrame()
{
	// small ring
	DrawCircleLines(cenX, cenY, rotationRadius, GRAY);

	// large ring
	DrawCircleLines(cenX, cenY, outerRadius, GRAY);



	// drawing ring
	DrawCircleLines(drawHeadRingCenterX,
					drawHeadRingCenterY,
					drawRingRadius, RED);



	drawCurve();



	// draw head base
	DrawCircle(drawHeadX, drawHeadY, 6, RED);
	
	// Draw line
	DrawLine(drawHeadRingCenterX, drawHeadRingCenterY, drawHeadX, drawHeadY, MAGENTA);

	// Draw head
	DrawCircle(drawHeadRingCenterX, drawHeadRingCenterY, 4, BLUE);
}
void Spirograph::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}

