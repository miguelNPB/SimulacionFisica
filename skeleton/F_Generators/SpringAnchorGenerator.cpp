#include "SpringAnchorGenerator.h"

SpringAnchorGenerator::SpringAnchorGenerator(ParticleSystem* sysRef, float elasticity, float restingLength) 
	: ForceGenerator(sysRef){
	this->elasticity = elasticity;
	this->restingLength = restingLength;
}

void SpringAnchorGenerator::applyForce(Particle* p) {
	Vector3 posRelativeOrigin = poolRef->getOrigin() - p->getPosition();

	float length = posRelativeOrigin.normalize();
	float deltaX = length - restingLength;

	Vector3 springForce = posRelativeOrigin * deltaX * elasticity;

	p->applyForce(springForce * p->getInvMass());
}