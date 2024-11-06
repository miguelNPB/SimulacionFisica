#include "WindGenerator.h"

WindGenerator::WindGenerator(ParticleSystem* sysRef, Vector3 direction, double strength) 
	: ForceGenerator(sysRef) {
	this->direction = direction;
	this->strength = strength;
}

void WindGenerator::applyForce(Particle* p) {
	Vector3 windVelocity = direction * strength;
	double k1 = 0.5; // coef rozamiento aire
	double k2 = 0;
	Vector3 aux = p->getVel() - windVelocity;

	Vector3 windForce = k1 * aux + k2 * (aux.magnitude() * aux);
	p->applyForce(windForce * p->getInvMass());
}