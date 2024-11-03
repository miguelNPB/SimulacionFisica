#pragma once
#include "RenderUtils.hpp"
#include <iostream>

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, 
		PxGeometryType::Enum geo = PxGeometryType::Enum::eSPHERE,
		float size = 1, double mass = 1, Vector4 color = Vector4(1,1,1,1));
	~Particle();

	void integrate(double t);

	void setAcceleration(Vector3 newAcc) { acc = newAcc; }
	Vector3 getAcceleration() { return acc; }

	void setDamping(float newDamp) { damping = newDamp; }
	float getDamping() { return damping; }

	PxTransform getTransform() { return pose; }

	double getMass() { return mass; }

	double timeAlive;
protected:
	PxTransform pose;
	RenderItem* renderItem;

	Vector3 vel;
	Vector3 acc;

	double mass;

	double damping = 1;
};

