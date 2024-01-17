#include <raylib.h>
#include <vector>


#ifndef SPIROGRAPH_H
#define SPIROGRAPH_H


class Spirograph
{
public:


	int width = 600;
	int height = 600;

// higher 
	float speed = .38; // Speed ~ 360 / myFrameRate

	float drawRingRadius = 60.0; // must be below 150
	float drawHeadDistToCen = 32.5; //  above 12 and below half of drawRingRadius
	Color linesColor = RED;
	float genMult = 1.5;
	float lineWidth = 1.0;


	bool pauseWhileControl = false;

	// all the initial variables
	float outerRadius = 150.0; // large ring radius
	float outerInnerRatio;   // ratio between the large ring and small ring
	// used to determin the angle of the inner circle
	float rotationRadius; // radius of the ring where the smaller circle will rotate around
	float headCurDegree;

	float currentRotation = 0.0; // current rotation of the smaller ring
	float myFrameRate = 120; // how many frames per secon

	Vector2 previousLoc = { -1.0, -1.0 }; // first location in the lines array
	std::vector<Vector2> pointsArr;

	float drawHeadX;
	float drawHeadY;

	float mainXCen;
	float mainYCen;

	float drawHeadRingCenterX;
	float drawHeadRingCenterY;


	void Main();
	void Start();         // Initialize game
	void EvalCurFrame();       // Update game (one frame)
	void DrawCurFrame();         // Draw game (one frame)
	void Update();  // Update and Draw (one frame)

	void drawHead();

	void drawCurve();

	void smallRing();

	void ringDraw(float inpRadius, Color inpColor);
};

#endif