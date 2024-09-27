#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc) {
	vel = Vel;
	pose = PxTransform(Pos);

	acc = Acc;

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + vel * t;
	vel = vel + acc * t;
}