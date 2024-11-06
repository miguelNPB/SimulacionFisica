#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(ParticleSystem* pool, Vector3 direction, double gravity)
	: ForceGenerator(pool) {
	this->direction = direction;
	this->gravity = gravity;


}

void GravityGenerator::applyForce(Particle* p) {

	p->applyForce(direction * p->getMass() * gravity);
}