#pragma once
#include "Particle.h"
#include <vector>

class ParticleController
{
public:
	void InitParticles(int particleAmount);
	void UpdateParticles(Camera2D cam);
	void DrawParticles();
	void ResetParticles(int particleAmount);
	void CreateParticle(Camera2D camera);

	bool positionLocked = false;
	float pullForce = 20;
private:
	std::vector<Particle> particles;
	Vector2 attractor = Vector2{ 0, 0 };
};