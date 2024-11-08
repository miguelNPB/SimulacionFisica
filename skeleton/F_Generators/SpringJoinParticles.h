#pragma once
#include "../Particle.h"

class SpringJoinParticles
{
public:
	SpringJoinParticles(Particle* p, Particle* other, float elasticity, float restingLength);

	void update(float t);
private:
	Particle* p;
	Particle* other;
	float elasticity;
	float restingLength;
};