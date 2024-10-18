#pragma once
#include "Particle.h"
#include "constants.h"

class Proyectile : public Particle
{
public:
	Proyectile(Vector3 Pos, Vector3 Vel, float mass, 
		float size = 1, Vector4 color = Vector4(1,1,1,1));

	~Proyectile();
private:
	float mass;
};

