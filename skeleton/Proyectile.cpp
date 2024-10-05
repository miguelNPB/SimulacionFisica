#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, float mass, float size, Vector4 color) 
	: Particle(Pos, Vel, size, color){
	
	Particle::setAcceleration({ getAcceleration().x, -GRAVITY, getAcceleration().z });

	this->mass = mass;
}

Proyectile::~Proyectile() {

}