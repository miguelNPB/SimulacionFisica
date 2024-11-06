#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, PxGeometryType::Enum geoType, float size, double mass, Vector4 color) {
	pose = PxTransform(Pos);

	vel = Vel;
	acc = Vector3(0, 0, 0);
	forces = Vector3(0, 0, 0);

	timeAlive = 0;

	this->mass = mass;

	switch (geoType) {
	case PxGeometryType::Enum::eSPHERE:
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
		break;
	case PxGeometryType::Enum::eBOX:
		renderItem = new RenderItem(CreateShape(PxBoxGeometry(size, size, size)), &pose, color);
		break;
	case PxGeometryType::Enum::ePLANE:
		renderItem = new RenderItem(CreateShape(PxPlaneGeometry()), &pose, color);
		break;
	default:
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
		break;
	}
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	timeAlive += t;

	pose.p += (vel * t);

	// acceleration
	Vector3 accTotal = acc + forces;
	vel = vel + accTotal * t;
		
	// damping
	vel = vel * std::pow(damping, t);

	forces = forces * 0;
}

void Particle::applyForce(const Vector3& force) {
	forces += force;
}