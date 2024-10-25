#pragma once
#include "constants.h"
#include <vector>
#include <functional>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector3 origin);

	void update(double t);

	// debe devolver TRUE si queremos que de destruyan
	void setDestroyCondition(std::function<bool(Particle* p)>);
	// tiempo en segundos
	void setDestroyConditionTimer(double time);

	void addParticleGenerator(ParticleGenerator* gen);

	void addForceGenerator(ForceGenerator* gen);

	void AddParticle(Particle* p);

	Vector3 getOrigin() { return origin; }

	void ToggleGravity() { gravity = !gravity; }
private:
	void killParticles();
	void updateParticles(double t);
	void updateGenerators(double t);
	void updateTimer(double t);
	double timer;

	Vector3 origin;

	std::function<bool(Particle*)> destroyCondition;
	std::vector<Particle*> pool;
	std::vector<ParticleGenerator*> generators;

	bool gravity = false;
};