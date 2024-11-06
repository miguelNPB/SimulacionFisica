#pragma once
#include "ForceGenerator.h"

class WhirlwindGenerator : public ForceGenerator
{
public:
	WhirlwindGenerator(ParticleSystem* sysRef, double radius, double height, double strength);

	virtual void applyForce(Particle* p) override;
private:
	double radius;
	double strength;
	double height;
};