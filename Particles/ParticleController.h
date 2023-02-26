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
private:
	std::vector<Particle> particles;
};