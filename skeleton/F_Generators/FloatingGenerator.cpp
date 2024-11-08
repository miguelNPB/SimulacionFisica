#include "FloatingGenerator.h"

FloatingGenerator::FloatingGenerator(ParticleSystem* refSys, float waterYpos, float volume, float density)
	: ForceGenerator(refSys), waterYpos(waterYpos), volume(volume), density(density){

}

void FloatingGenerator::applyForce(Particle* p) {
	 

	float immersed = 0.0;
	if (p->getPosition().y - waterYpos > p->getSize() * 0.5)
		immersed = 0.0;
	else if (waterYpos - p->getPosition().y > p->getSize() * 0.5)
		immersed = 1.0;
	else
		immersed = (p->getPosition().y - waterYpos) / p->getSize() * 0.5;

	Vector3 buoyancyForce = Vector3(0, 0, 0);
	buoyancyForce.y = density * volume * immersed;

	p->applyForce(buoyancyForce * p->getInvMass());
}