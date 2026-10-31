#include "raylib.h"
#include <cmath>
#include <vector>

// PRESS SPACE TO INCREASE THE SIZE OF THE HYPOTROCHOID

int main()
{
	std::vector<float> Rvalues = { 4,5,7,8,9,10,11,12 }; // Big Circle Radius (Fixed for this example)
	std::vector<float> rvalues = { 3,3,4,5,5,7,6,7 }; // Small Circle Radius (Fixed for this example)
	std::vector<float> dvalues = { 5,5,6,7,7,9,8,9 }; // Pen distance (Fixed for this example)

	int hcLookingAt = 0; // what hypotrochoid we are looking at currently

	const float speed = 0.03f; // how much theta (θ) grows each frame (CHANGE TO YOUR LIKING)
	const float unit = 20; // pixels per graph unit

	InitWindow(800, 800, "Hypotrochoid");
	SetTargetFPS(60);

	float k = Rvalues[hcLookingAt] - rvalues[hcLookingAt]; // big circle rad - small circle rad
	const Vector2 graphPos = { 400, 400 };    // Graphs origin pos


	// lambda to convert points to pixels
	auto screen = [&](float x, float y)
		{
			return Vector2{ graphPos.x + unit * x, graphPos.y - unit * y };
		};

	std::vector<Vector2> trail; // where the dots are stored
	float theta = 0; // θ (the angle)

	//-----------------------------------------------------

	while (!WindowShouldClose())
	{
		// Change size & Reset hypotrochoid
		if (IsKeyPressed(KEY_SPACE))
		{
			trail.clear();
			theta = 0;
			if (hcLookingAt < Rvalues.size() - 1)
			{
				hcLookingAt++;
			}
			else
			{
				hcLookingAt = 0;
			}
			k = Rvalues[hcLookingAt] - rvalues[hcLookingAt];
		}

		//-------------------------------------------------

		// Hypotrochoid fomula
		float x = k * cosf(theta) + dvalues[hcLookingAt] * cosf(k / rvalues[hcLookingAt] * theta);
		float y = k * sinf(theta) - dvalues[hcLookingAt] * sinf(k / rvalues[hcLookingAt] * theta);

		//-------------------------------------------------

		Vector2 pen = screen(x, y);
		Vector2 C = screen(k * cosf(theta), k * sinf(theta));   // center of the rolling circle

		if (theta <= 2 * PI * rvalues[hcLookingAt]) { trail.push_back(pen); theta += speed; } // while the pen is not at its origin add a new line

		BeginDrawing();
		ClearBackground(WHITE);

		for (size_t i = 1; i < trail.size(); i++)
		{
			DrawLineEx(trail[i - 1], trail[i], 3, RED); // (CHANGE COLOR TO YOUR LIKING)
		}

		DrawRing(graphPos, Rvalues[hcLookingAt] * unit - 1.5f, Rvalues[hcLookingAt] * unit + 1.5f, 0, 360, 100, BLUE); // Big circle
		DrawRing(C, rvalues[hcLookingAt] * unit - 1.5f, rvalues[hcLookingAt] * unit + 1.5f, 0, 360, 100, BLACK); // Rolling circle
		DrawLineEx(C, pen, 1.5f, BLACK); // Pen arm
		DrawCircleV(C, 4, BLACK); // Center black dot
		DrawCircleV(pen, 5, RED); // Pen tip dot
		EndDrawing();
	}
	CloseWindow();
}