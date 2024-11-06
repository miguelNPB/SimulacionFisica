#include "CustomParticleGenerator.h"

CustomParticleGenerator::CustomParticleGenerator(ParticleSystem* sysRef, double spawnDelay, std::function<Particle*()> func)
	: ParticleGenerator(spawnDelay) {
	this->func = func;
	this->sysRef = sysRef;
}

void CustomParticleGenerator::spawnParticle() {
	Particle* p = func();

	sysRef->AddParticle(p);
}