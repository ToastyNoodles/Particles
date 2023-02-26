#include "ParticleController.h"
#include <raylib.h>
#include <string>

const int maxParticles = 40000;
Camera2D camera;

std::string inputText;
std::string infoText;

int main()
{
	InitWindow(800, 800, "Particle Sim Thingy");
	SetTargetFPS(60);

	IsWindowFullscreen();

	camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenWidth() / 2};
	camera.target = Vector2{ 0, 0 };
	camera.rotation = 0;
	camera.zoom = 0.5;

	ParticleController particleController{};
	particleController.InitParticles(maxParticles);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_R))
		{
			particleController.ResetParticles(maxParticles);
		}

		if (GetMouseWheelMoveV().y > 0) {
			camera.zoom += 0.01;
		}
		if (GetMouseWheelMoveV().y < 0) {
			if (camera.zoom >= 0.02)
			{
				camera.zoom -= 0.01;
			}
		}

		if (IsKeyDown(KEY_W))
		{
			camera.target.y -= 50;
		}
		if (IsKeyDown(KEY_S))
		{
			camera.target.y += 50;
		}
		if (IsKeyDown(KEY_A))
		{
			camera.target.x -= 50;
		}
		if (IsKeyDown(KEY_D))
		{
			camera.target.x += 50;
		}

		particleController.UpdateParticles(camera);

		ClearBackground(BLACK);
		BeginDrawing();
		BeginMode2D(camera);

		particleController.DrawParticles();

		EndMode2D();

		inputText = "Scroll Wheel - Zoom | Spacebar - Lock Attractor | R - Reset Particles";
		infoText = "Camera Zoom: " + std::to_string(camera.zoom) + " | Particle Count: " + std::to_string(maxParticles) + " | Locked State: " + std::to_string(particleController.positionLocked) + " | Speed: " + std::to_string(particleController.pullForce);
		DrawText(inputText.c_str(), 5, 23, 18, WHITE);
		DrawText(infoText.c_str(), 5, 5, 18, WHITE);

		EndDrawing();
	}

	return 0;
}