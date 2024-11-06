#pragma once
#include "Particle.h"
#include "ParticleSystem.h"

class ParticleGenerator
{
public:
	ParticleGenerator(double spawnDelay = 0);

	virtual void spawnParticle() = 0;

	void update(double t);
protected:
	double timer = 0;
private:
	double spawnDelay;
	double timerSpawn;
};

