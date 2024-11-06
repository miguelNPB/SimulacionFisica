#pragma once
#include "ForceGenerator.h"

class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(ParticleSystem* sysRef, Vector3 direction, double strength);

	virtual void applyForce(Particle* p) override;
private:
	Vector3 direction;
	double strength;
};