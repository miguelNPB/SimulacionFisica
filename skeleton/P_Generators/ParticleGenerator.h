#pragma once
#include "../Particle.h"
#include "../ParticleSystem.h"

class ParticleGenerator
{
public:
	ParticleGenerator(double spawnDelay = 0) {
		this->spawnDelay = spawnDelay;
		this->timerSpawn = timer + spawnDelay;
	}

	virtual void spawnParticle() = 0;

	void update(double t) {
		timer += t;
		if (timer > timerSpawn) {

			spawnParticle();

			timerSpawn = timer + spawnDelay;
		}
	}
protected:
	double timer = 0;
private:
	double spawnDelay;
	double timerSpawn;
};

