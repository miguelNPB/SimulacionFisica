#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(ParticleSystem* sysRef, float radius, float strength, float explosionTime);

	virtual void applyForce(Particle* p) override;

	virtual void update(float t) override;

	void explode();
private:
	bool ready;
	float timer;
	float timeToEndExplosion;
	float explosionTime;

	float radius;
	float strength;
};