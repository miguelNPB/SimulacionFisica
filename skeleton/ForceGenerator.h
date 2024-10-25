#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(std::vector<Particle*>* poolRef) {
		this->poolRef = poolRef;
	}

	virtual void applyForce(Particle* p) = 0;

	void update(double t) {
		for (auto p : (*poolRef)) {
			applyForce(p);
		}
	}
protected:
	std::vector<Particle*>* poolRef;
};