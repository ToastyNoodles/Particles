#include "ParticleController.h"
#include <raylib.h>
#include <string>

const int maxParticles = 40000;
Camera2D camera;

std::string text;

int main()
{
	InitWindow(800, 800, "Particle Sim Thingy");
	SetTargetFPS(60);

	IsWindowFullscreen();

	camera.offset = Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenWidth() / 2};
	camera.target = Vector2{ 0, 0 };
	camera.rotation = 0;
	camera.zoom = 1;

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

		particleController.UpdateParticles(camera);

		ClearBackground(BLACK);
		BeginDrawing();
		BeginMode2D(camera);
		particleController.DrawParticles();
		EndMode2D();
		text = "Scroll Wheel - Zoom | Spacebar - Lock Attractor | R - Reset Particles";
		DrawText(text.c_str(), 5, 5, 20, WHITE);
		DrawFPS(5, 25);
		EndDrawing();
	}

	return 0;
}