#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, float size, Vector4 color) {
	pose = PxTransform(Pos);

	vel = Vel;
	acc = Vector3(0, 0, 0);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	// damping
	vel = vel * std::pow(damping, t); 

	// acceleration
	vel = vel + acc * t;

	pose.p += (vel * t);
}