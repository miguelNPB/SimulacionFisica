#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pose = PxTransform(Pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + t * vel;
}