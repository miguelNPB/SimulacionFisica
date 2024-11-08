#pragma once
#include "ForceGenerator.h"

class FloatingGenerator : public ForceGenerator
{
public:
	FloatingGenerator(ParticleSystem* refSys, float waterYpos, float volume, float density);

	virtual void applyForce(Particle* p) override;
private:
	float waterYpos;
	float volume;
	float density;
};