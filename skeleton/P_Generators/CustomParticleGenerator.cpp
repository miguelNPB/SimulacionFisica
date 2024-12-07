#include "CustomParticleGenerator.h"

CustomParticleGenerator::CustomParticleGenerator(ParticleSystem* sysRef, double spawnDelay, std::function<Particle*()> func)
	: ParticleGenerator(spawnDelay) {
	this->func = func;
	this->sysRef = sysRef;
	this->active = true;
}

void CustomParticleGenerator::spawnParticle() {
	if (active) {
		Particle* p = func();

		sysRef->AddParticle(p);
	}
}