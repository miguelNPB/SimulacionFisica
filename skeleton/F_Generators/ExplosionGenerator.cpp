#include "ExplosionGenerator.h"
#include <cmath>

ExplosionGenerator::ExplosionGenerator(ParticleSystem* sysRef, float radius, float strength, float explosionTime)
	: ForceGenerator(sysRef) {
	this->radius = radius;
	this->strength = strength;
	this->explosionTime = explosionTime;
	this->timeToEndExplosion = -1;
	timer = 0;
	ready = false;
}

void ExplosionGenerator::applyForce(Particle* p) {
	Vector3 explosionForce = Vector3(0, 0, 0);

	if ((p->getPosition() - poolRef->getOrigin()).magnitude() < radius) {
		Vector3 centerToP = Vector3(p->getPosition().x - poolRef->getOrigin().x, 
			p->getPosition().y - poolRef->getOrigin().y, p->getPosition().z - poolRef->getOrigin().z);

		explosionForce = (strength / pow(radius, 2)) * centerToP * pow(std::exp(1.0), (-timer / timeToEndExplosion));
	}

	p->applyForce(explosionForce);
}

void ExplosionGenerator::update(float t) {
	timer += t;
	if (!ready && timer < timeToEndExplosion) {
		ForceGenerator::update(t);
	}
	else if (!ready)
		ready = true;
}

void ExplosionGenerator::explode() {
	if (ready) {
		std::cout << "explosion" << "\n";
		timeToEndExplosion = timer + explosionTime;
		ready = false;
	}
}