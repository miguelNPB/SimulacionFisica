#include "RB_WindGenerator.h"
#include <iostream>

RB_WindGenerator::RB_WindGenerator(RB_System* sysRef, Vector3 pos,
	Vector3 direction, float radius, float strength) : RB_ForceGenerator(sysRef) {
	this->strength = strength;
	this->radius = radius;
	this->direction = direction;


	tr = new PxTransform(pos);
#ifdef DEBUG
	PxShape* shape = CreateShape(PxSphereGeometry(radius));
	RenderItem* item = new RenderItem(shape, tr, color);
#endif
}

void RB_WindGenerator::applyForce(std::shared_ptr<RB> rb) {
	
	if ((rb->getRigidBody()->getGlobalPose().p - tr->p).magnitude() < radius) {
		Vector3 windVelocity = direction * strength;
		float k1 = 0.5; // coef rozamiento aire
		float k2 = 0;
		Vector3 aux = rb->getRigidBody()->getLinearVelocity() - windVelocity;

		Vector3 windForce = k1 * aux + k2 * (aux.magnitude() * aux);
		rb->getRigidBody()->addForce(windForce);
	}
}