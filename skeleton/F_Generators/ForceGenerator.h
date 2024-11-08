#pragma once
#include "../Particle.h"
#include "../ParticleSystem.h"

class ForceGenerator
{
public:
	ForceGenerator(ParticleSystem* poolRef) {
		this->poolRef = poolRef;
	}

	virtual void applyForce(Particle* p) = 0;

	virtual void update(float t) {
		for (Particle* p : *(poolRef->getPoolRef())) {
			applyForce(p);
		}
	}
protected:
	ParticleSystem* poolRef;
};