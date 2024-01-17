#include <raylib.h>
#include <vector>

#include "Spirograph.H"


void Spirograph::ringDraw(float inpRadius, Color inpColor)
{
	DrawCircleLines(mainXCen, mainYCen, inpRadius * genMult, inpColor);
}


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

			DrawLine (curP.x, curP.y, preP.x, preP.y, linesColor);
		}
		previousLoc = Vector2{ drawHeadX, drawHeadY };
	}
}

void Spirograph::smallRing()
{
	drawHeadRingCenterX = mainXCen + sin(currentRotation * DEG2RAD) * rotationRadius * genMult;
	drawHeadRingCenterY = mainYCen + cos(currentRotation * DEG2RAD) * rotationRadius * genMult;


	DrawCircleLines (drawHeadRingCenterX,
		   drawHeadRingCenterY,
		   drawRingRadius * genMult, RED);
}


void Spirograph::Main()
{
	InitWindow(width, height, "Spirograph");
	SetTargetFPS(60);

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
	mainXCen = width / 2;
	mainYCen = (height - 100) / 2 + 100;
	rotationRadius = outerRadius - drawRingRadius; // rotation ring radius calculated



}


void Spirograph::EvalCurFrame()
{

}
void Spirograph::DrawCurFrame()
{

}
void Spirograph::Update()
{

	ringDraw(rotationRadius, Color{ 200, 200, 200, 100 });  // rotation ring

	ringDraw(outerRadius, BLACK); // outer ring
	rotationRadius = outerRadius - drawRingRadius; // rotation ring radius calculated


	outerInnerRatio = outerRadius / (drawRingRadius - drawHeadDistToCen);

	// inner little rotating around


	smallRing();
	drawHead();
	if (!pauseWhileControl)
	{
		currentRotation += (speed * 3); // 3 is default in 120 fps
		drawCurve();
	}

}


void Spirograph::drawHead()
{
	if (!pauseWhileControl)
		headCurDegree = currentRotation * outerInnerRatio;
	else
		headCurDegree = 1;

	//println("currentRotation" + currentRotation);
	//println("headCurDegree" + headCurDegree);

	drawHeadX = drawHeadRingCenterX + sin(headCurDegree * DEG2RAD) * drawHeadDistToCen;
	drawHeadY = drawHeadRingCenterY + cos(headCurDegree * DEG2RAD) * drawHeadDistToCen;



	DrawCircleLines (drawHeadX, drawHeadY, 2, RED);


	DrawLine (drawHeadRingCenterX, drawHeadRingCenterY, drawHeadX, drawHeadY, MAGENTA);


	DrawCircleLines(drawHeadRingCenterX, drawHeadRingCenterY, 3, YELLOW);
}