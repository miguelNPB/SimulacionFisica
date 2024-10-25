#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(std::vector<Particle*>* pool, Vector3 direction, double gravity);

	virtual void applyForce(Particle* p) override;
private:
	Vector3 direction;
	double gravity;
};

