#pragma once
#include <raylib.h>
#include <cstdlib>

struct Particle
{
	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	const float mass = (float)GetRandomValue(1000, 30000);
	const float terminalVelocity = mass * 20;
	Rectangle rect = Rectangle{ (float)GetRandomValue(-GetScreenWidth(), GetScreenWidth()), (float)GetRandomValue(-GetScreenHeight(), GetScreenHeight()), mass / 500, mass / 500};

	Color color = Color{ (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
	Vector2 velocity = Vector2{ 0, 0 };
};