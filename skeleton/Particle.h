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

	Vector3 getVel() { return vel; }
	void setVel(const Vector3& newVel) { vel = newVel; }

	void setAcceleration(const Vector3& newAcc) { acc = newAcc; }
	Vector3 getAcceleration() { return acc; }

	void applyForce(const Vector3& force);

	void setDamping(float newDamp) { damping = newDamp; }
	float getDamping() { return damping; }

	PxTransform getTransform() { return pose; }
	Vector3 getPosition() { return pose.p; }

	double getInvMass() { return 1.0 / mass; }
	double getMass() { return mass; }

	double timeAlive;
protected:
	PxTransform pose;
	RenderItem* renderItem;

	Vector3 vel;
	Vector3 acc;

	Vector3 forces;
	double mass;

	double damping = 1;
};

