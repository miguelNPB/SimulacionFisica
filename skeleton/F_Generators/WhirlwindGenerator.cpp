#include "WhirlwindGenerator.h"

WhirlwindGenerator::WhirlwindGenerator(ParticleSystem* sysRef, float radius, float height, float strength)
	: ForceGenerator(sysRef) {
	this->strength = strength;
	this->radius = radius;
	this->height = height;
}

void WhirlwindGenerator::applyForce(Particle* p) {
	if ((p->getPosition() - poolRef->getOrigin()).magnitudeSquared() > radius * radius)
		return;

	Vector3 whirlwindVel = strength * Vector3(
		-(p->getPosition().z - poolRef->getOrigin().z),
		height - (p->getPosition().y - poolRef->getOrigin().y),
		p->getPosition().x - poolRef->getOrigin().x);

	p->applyForce(whirlwindVel * p->getInvMass());
}