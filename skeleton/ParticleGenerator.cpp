#include "ParticleGenerator.h"

// el delay en segundos
ParticleGenerator::ParticleGenerator(double spawnDelay) {

	this->spawnDelay = spawnDelay;
	this->timerSpawn = timer + spawnDelay;
}

void ParticleGenerator::update(double t) {
	timer += t;
	if (timer > timerSpawn) {

		spawnParticle();

		timerSpawn = timer + spawnDelay;
	}
}