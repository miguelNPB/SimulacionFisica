#pragma once
#include "ForceGenerator.h"

class WhirlwindGenerator : public ForceGenerator
{
public:
	WhirlwindGenerator(ParticleSystem* sysRef, float radius, float height, float strength);

	virtual void applyForce(Particle* p) override;
private:
	float radius;
	float strength;
	float height;
};