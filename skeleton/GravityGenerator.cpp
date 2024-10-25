#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(std::vector<Particle*>* pool, Vector3 direction, double gravity)
	: ForceGenerator(pool) {
	this->direction = direction;
	this->gravity = gravity;


}

void GravityGenerator::applyForce(Particle* p) {

	p->setAcceleration({ p->getAcceleration() + (direction * gravity) });
}