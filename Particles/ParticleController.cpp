#include "ParticleController.h"
#include <raymath.h>

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
			DrawRectangle(attractor.x, attractor.y, 50, 50, YELLOW);
		}
	}
	else
	{
		if (!positionLocked)
		{
			attractor = GetScreenToWorld2D(GetMousePosition(), cam);
		}
	}

	if (IsKeyDown(KEY_UP))
	{
		pullForce += 1;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		pullForce -= 1;
	}

	for (int i = 0; i < particles.size(); i++)
	{
		//float distance = Vector2Distance(attractor, Vector2{ particles[i].rect.x, particles[i].rect.y });
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
	}

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
		if (positionLocked)
		{
			DrawRectangle(attractor.x - 150, attractor.y - 150, 300, 300, YELLOW);
		}
	}
}

void ParticleController::ResetParticles(int particleAmount)
{
	particles.clear();
	InitParticles(particleAmount);
}

void ParticleController::CreateParticle(Camera2D camera)
{
	Particle newParticle;
	newParticle.rect.x = GetScreenToWorld2D(GetMousePosition(), camera).x;
	newParticle.rect.y = GetScreenToWorld2D(GetMousePosition(), camera).y;
	particles.push_back(newParticle);
}