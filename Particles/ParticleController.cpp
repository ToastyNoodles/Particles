#include "ParticleController.h"
#include <raymath.h>

const float pullForce = 60;
Vector2 attractor = Vector2{ 0, 0 };
bool positionLocked = false;

void ParticleController::InitParticles(int particleAmount)
{
	for (int i = 0; i < particleAmount; i++)
	{
		particles.push_back(Particle{});
	}
}

void ParticleController::UpdateParticles(Camera2D cam)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		positionLocked = !positionLocked;
		if (positionLocked)
		{
			attractor = GetScreenToWorld2D(GetMousePosition(), cam);
		}
	}
	else
	{
		if (!positionLocked)
		{
			attractor = GetScreenToWorld2D(GetMousePosition(), cam);
		}
	}

	for (int i = 0; i < particles.size(); i++)
	{
		float distance = Vector2Distance(attractor, Vector2{ particles[i].rect.x, particles[i].rect.y });
		Vector2 target = Vector2Subtract(attractor, Vector2{ particles[i].rect.x, particles[i].rect.y });
		target = Vector2Divide(Vector2Multiply(target, Vector2{ pullForce, pullForce }), Vector2{ particles[i].mass, particles[i].mass });

		if (particles[i].rect.x > GetMousePosition().x)
		{
			particles[i].velocity.x += target.x;
		}
		if (particles[i].rect.x < GetMousePosition().x)
		{
			particles[i].velocity.x += target.x;
		}
		if (particles[i].rect.y > GetMousePosition().y)
		{
			particles[i].velocity.y += target.y;
		}
		if (particles[i].rect.y < GetMousePosition().y)
		{
			particles[i].velocity.y += target.y;
		}

		//printf("Particle [%i] | Velocity [%.3f, %.3f] | Force [%.3f, %.3f] | Distance [%.0f] | Mass [%.0f]\n", i, particles[i].velocity.x, particles[i].velocity.y, target.x, target.y, distance, particles[i].mass);
	}

	//Move Particles
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].rect.x += particles[i].velocity.x;
		particles[i].rect.y += particles[i].velocity.y;
	}
}

void ParticleController::DrawParticles()
{
	for (int i = 0; i < particles.size(); i++)
	{
		DrawRectangleRec(particles[i].rect, particles[i].color);
	}
}

void ParticleController::ResetParticles(int particleAmount)
{
	particles.clear();
	InitParticles(particleAmount);
}