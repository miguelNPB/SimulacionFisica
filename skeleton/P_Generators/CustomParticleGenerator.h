#pragma once
#include "ParticleGenerator.h"
#include <functional>

class CustomParticleGenerator : public ParticleGenerator
{
public:
	CustomParticleGenerator(ParticleSystem* sysRef, double spawnDelay,
		std::function<Particle*()> func);

	void spawnParticle() override;

	void toggleActive() { active = !active; }
private:
	bool active;
	ParticleSystem* sysRef;
	std::function<Particle*()> func;
};