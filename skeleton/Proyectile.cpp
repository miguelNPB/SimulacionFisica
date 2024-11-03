#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, PxGeometryType::Enum geoType, float mass, float size, Vector4 color)
	: Particle(Pos, Vel, geoType, size, mass, color){
	
	Particle::setAcceleration({ getAcceleration().x, getAcceleration().x, getAcceleration().z});
}

Proyectile::~Proyectile() {

}
