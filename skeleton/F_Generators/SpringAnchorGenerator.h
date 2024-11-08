#pragma once
#include "ForceGenerator.h"

class SpringAnchorGenerator : public ForceGenerator
{
public:
	SpringAnchorGenerator(ParticleSystem* sysRef, float elasticity, float restingLength);

	virtual void applyForce(Particle* p);
private:
	float elasticity;
	float restingLength;
};

