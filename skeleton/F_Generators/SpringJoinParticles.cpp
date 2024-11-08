#include "SpringJoinParticles.h"

SpringJoinParticles::SpringJoinParticles(Particle* p, Particle* other, float elasticity, float restingLength) {
	this->elasticity = elasticity;
	this->restingLength = restingLength;
	this->p = p;
	this->other = other;
}

void SpringJoinParticles::update(float t) {
	Vector3 posRelativeOrigin = other->getPosition() - p->getPosition();

	float length = posRelativeOrigin.normalize();
	float deltaX = length - restingLength;

	Vector3 springForce = posRelativeOrigin * deltaX * elasticity;

	p->applyForce(springForce);
}