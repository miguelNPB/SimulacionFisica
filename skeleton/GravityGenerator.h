#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(ParticleSystem* sysRef, Vector3 direction, double gravity);

	virtual void applyForce(Particle* p) override;
private:
	Vector3 direction;
	double gravity;
};

