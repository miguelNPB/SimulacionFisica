#pragma once
#include "RenderUtils.hpp"
#include <iostream>

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;

	Vector3 acc;

	float size = 1;
	Vector4 color;

	double damping = 0.999;
};

