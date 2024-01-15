#include <iostream>
#include <raylib.h>
#include <sstream>

#include "games.h"
#include <vector>

#include <raymath.h>


using namespace std;




void ball_010()
{
	Color Blue = Color{ 50, 50, 255,  255 };
	Color Dark_Green = Color{ 20, 160, 133, 255 };

	int posX = 100, posY = 100;
	float speedX = 5, speedY = 5;
	int r = 15;

	const int width = 1280;
	const int height = 720;
	InitWindow(width, height, "My Game");

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(Dark_Green);

		posX += speedX;
		posY += speedY;

		if (posX + r >= width || posX - r <= 0)
			speedX *= -1;

		if (posY + r >= height || posY - r <= 0)
			speedY *= -1;


		std::string speedXText = "Speed X: " + std::to_string(speedX);
		std::string speedYText = "Speed Y: " + std::to_string(speedY);


		// we gotta convert the string to s-style const character
		DrawText(speedXText.c_str(), posX + 20, posY - 20, 24, WHITE);
		DrawCircle(posX, posY, r, WHITE);
		speedX *= 1.001f;
		speedY *= 1.001f;

		EndDrawing();
	}

	CloseWindow();
}



void bouncingBall_012()
{
	InitWindow(600, 600, "Ball Animation");

	int width = 600;
	int height = 600;

	// Load ball image
	Texture2D ballTex = LoadTexture("Resource Files/soccerball.png");


	Vector2 ballPos = { width / 2 - ballTex.width / 2, height / 2};
	float yRate = 2.0f;



	SetTargetFPS(60); // Set the desired frame rate

	while (!WindowShouldClose())
	{
		// Update the ball's position
		yRate += 0.5f;
		ballPos.y += yRate;

		// Collision with the bottom
		if (ballPos.y > height - ballTex.height)
		{
			ballPos.y = height - ballTex.height;
			yRate *= -0.9f;
		}
		else if (ballPos.y <= 0)
		{
			yRate *= -1;
		}

		// Check for mouse release
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			ballPos.y = 150;
		}

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(ballTex,
					ballPos.x,
					ballPos.y,
					WHITE);

		EndDrawing();
	}

	// De-Initialization
	UnloadTexture(ballTex);  // Unload the texture
	CloseWindow();           // Close the window

}


void ui_button_011()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Button");

	Rectangle btnBounds = { 100, 100, 100, 44 };
	Color buttonColor = BLUE;


	Vector2 mousePoint = { 0.0f, 0.0f }; // for caching

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		mousePoint = GetMousePosition();

		buttonColor = BLUE;
		if (CheckCollisionPointRec(mousePoint, btnBounds))
		{
			buttonColor = GREEN;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				buttonColor = RED;
		}


		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawRectangleRounded(btnBounds, 0.1, 12, buttonColor);



		EndDrawing();
	}

	CloseWindow();
}

// This function needs a lot of review
void collisions_009()
{
	InitWindow(600, 600, "Collision");

	Rectangle boxA = { 50, 275, 50, 50 };
	int gravity = 10;


	// Box B: Static Box at the bottom
	Rectangle boxB = {50, 500, 500, 20 };

	bool collision = false;



	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		boxA.y += gravity;


		// Bounce box on x screen limits
		if (((boxA.y + boxA.height) >= GetScreenHeight()) || (boxA.y <= 0)) gravity *= -1;



		// Check boxes collision
		collision = CheckCollisionRecs(boxA, boxB);

		// Get collision rectangle (only on collision)
		if (collision) 





		BeginDrawing();

		ClearBackground(GRAY);


		DrawRectangleRec(boxA, GOLD);
		DrawRectangleRec(boxB, BLUE);

		if (collision)
		{

			// Draw collision message
			DrawText("COLLISION!", 
				GetScreenWidth() / 2 , 
				GetScreenHeight() / 2,
				20, 
				BLACK);


		}


		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
}


void triangle_corners_007()
{
	Vector2 leftCorner, rightCorner, topCorner;
	bool dragging = false;

	// Initialization of the window
	const int screenWidth = 500;
	const int screenHeight = 500;

	InitWindow(screenWidth, screenHeight, "Triangle Drawer");

	SetTargetFPS(60);  // Set the desired frame rate

	// Initialize corners
	leftCorner = Vector2{ 50, screenHeight - 50 };
	rightCorner = Vector2{ screenWidth - 50, screenHeight - 50 };
	topCorner = Vector2{ screenWidth / 2, screenHeight / 2 };

	while (!WindowShouldClose())
	{
		// on each update, let's make the dragging false first
		dragging = false;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			dragging = true;
			Vector2 mouseLoc = Vector2{ (float)GetMouseX(),  (float)GetMouseY() };

			float leftDist = Vector2Distance(mouseLoc, leftCorner);
			float rightDist = Vector2Distance(mouseLoc, rightCorner);
			float tipDist = Vector2Distance(mouseLoc, topCorner);

			if (leftDist < rightDist && leftDist < tipDist)
				leftCorner = mouseLoc;
			else if (rightDist < leftDist && rightDist < tipDist)
				rightCorner = mouseLoc;
			else
				topCorner = mouseLoc;
		}
		else
			dragging = false;

		BeginDrawing();
		ClearBackground({ 30, 30, 30, 255 });

		DrawTriangle(leftCorner, rightCorner, topCorner, GRAY);

		EndDrawing();
	}

	CloseWindow();  // Close window and OpenGL context


}

void draw_polygone_006()
{
	int numOfCorners = 6;


	// vector is the array of STD
	std::vector<Vector2> cornersArr;

	const int screenWidth = 500;
	const int screenHeight = 500;

	InitWindow(screenWidth, screenHeight, "Polygon Drawing");
	SetTargetFPS(10);

	Vector2 viewCenter = Vector2{ screenWidth / 2.0, screenHeight / 2.0 };

	//cornersArr.push_back(Vector2{ viewCenter.x, viewCenter.y });

	while (!WindowShouldClose()) {

		if (cornersArr.size() < numOfCorners) {
			float angle = 360.0 / numOfCorners;
			float x = cos(DEG2RAD * (angle * cornersArr.size())) * 100 + viewCenter.x;
			float y = sin(DEG2RAD * (angle * cornersArr.size())) * 100 + viewCenter.y;
			cornersArr.push_back(Vector2{ x, y });
		}

		// Draw
		BeginDrawing();
		ClearBackground({ 80, 80, 80, 255 });

		if (cornersArr.size() > 2)
			// use <= for clarification
			for (int i = 0; i <= cornersArr.size() - 2; i++)
			{
				// draw all in blue, except for the current one
				if (i == cornersArr.size() - 2)
					DrawTriangle(viewCenter, cornersArr[i + 1], cornersArr[i], BLUE);
				else
					DrawTriangle(viewCenter, cornersArr[i + 1], cornersArr[i], RED);

			}


		// Connect the last one
		DrawTriangle(viewCenter, cornersArr.front(), cornersArr.back(),
			WHITE);

		EndDrawing();

		// Mouse Pressed
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			cornersArr.clear();
			numOfCorners = GetRandomValue(5, 20);
		}
	}

	CloseWindow();

}




void mouse_drag_005()
{
	int widthHeight = 160;
	int y;
	int x = 160;
	int dist = 80;


	InitWindow(500, 500, "Mouse");
	SetTargetFPS(60); // Set FPS

	BlendMode blendMode = BLEND_ADDITIVE;

	while (!WindowShouldClose())
	{
		// Update variables
		y = GetMouseY() - 400;

		// Start Drawing
		BeginDrawing();
		ClearBackground({ 30, 30, 30, 255 });


		DrawCircle(x + dist / 2, 400 - y, widthHeight / 2, BLUE); // Blue circle


		BeginBlendMode(blendMode);

		DrawCircle(x - dist / 2, 400 + y, widthHeight / 2, GREEN); // Green circle
		EndBlendMode();


		EndDrawing();
	}

	CloseWindow();
}

void draw_image_004()
{
	// IMPORTANT
	// You must manually create a folder called "Resource Files" in the 
	// directory where main.cpp exists and then add images to it


	int w = 500, h = 500;

	InitWindow(w, h, "Image");

	// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

	Image dog = LoadImage("Resource Files/dog.png");
	if (dog.data != NULL)
		cout << "Found Image" << endl;
	else
		cout << "Image is Null" << endl;
	
	// you must re-size to get the image size that you want. 
	ImageResize(&dog, 100, 100);

	ImageCrop (&dog, Rectangle{	0,
								0, 
								100,
								100 }); // Crop resulting image


	Texture2D texture = LoadTextureFromImage(dog);      // Image converted to texture, uploaded to GPU memory (VRAM)
	UnloadImage(dog);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM


	SetTargetFPS(60);
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

		ClearBackground(RED);

		DrawTexture(texture,
			0,
			0,
			WHITE);


		EndDrawing();
	}

	UnloadTexture(texture);

	CloseWindow();
}



void inputs_003()
{

	InitWindow(500, 500, "My Game");

	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(PURPLE);

		if (IsKeyDown(KEY_SPACE))
		{
			cout << "Space Pressed";

			string mouseX = "Mouse X: " + to_string(GetMouseX());
			string mouseY = "Mouse Y: " + to_string(GetMouseY());


			// we gotta convert the string to s-style const character
			DrawText(mouseX.c_str(),
				GetScreenWidth() / 2,
				GetScreenHeight() / 2,
				24,
				WHITE);

			DrawText(mouseY.c_str(),
				GetScreenWidth() / 2 + 20,
				GetScreenHeight() / 2 - 20,
				24,
				WHITE);
		}

		EndDrawing();
	}

	CloseWindow();
}




void drawing_002()
{
	InitWindow(500, 500, "My Game");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(PURPLE);

		DrawLine(20, 20, 100, 20, BLACK);

		DrawCircle(100, 100, 80, BLUE);

		DrawRectangle(150, 250, 150, 150, RED);

		DrawPoly(Vector2{ 400, 300 },
			8,
			80,
			0, // how much it's rotated
			BLACK);

		EndDrawing();
	}

	CloseWindow();
}



void simple_draw_001()
{
	InitWindow(500, 500, "My Game");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(Color{ 0, 0, 0, 255 });

		std::string txt = "HI";


		DrawText(txt.c_str(), 180, 80, 24, RED);
		DrawCircle(100, 100, 20, WHITE);
		EndDrawing();
	}

	CloseWindow();
}


void test_000()
{

}