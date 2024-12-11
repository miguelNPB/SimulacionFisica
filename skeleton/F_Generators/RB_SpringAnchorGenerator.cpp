#include "RB_SpringAnchorGenerator.h"

RB_SpringAnchorGenerator::RB_SpringAnchorGenerator(RB_System* sysRef, Vector3 origin, float elasticity, float restingLength)
	: RB_ForceGenerator(sysRef) {
	this->elasticity = elasticity;
	this->restingLength = restingLength;
	this->origin = origin;

}

void RB_SpringAnchorGenerator::applyForce(std::shared_ptr<RB> rb) {
	Vector3 posRelativeOrigin = origin - rb->getRigidBody()->getGlobalPose().p;

	float length = posRelativeOrigin.normalize();
	float deltaX = length - restingLength;

	Vector3 springForce = posRelativeOrigin * deltaX * elasticity;

	rb->getRigidBody()->addForce(springForce);
}