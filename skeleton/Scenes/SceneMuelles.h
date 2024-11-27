#pragma once
#include "Scene.h"
#include "../ParticleSystem.h"
#include "../F_Generators/SpringAnchorGenerator.h"
#include "../F_Generators/GravityGenerator.h"
#include "../F_Generators/SpringJoinParticles.h"

class SceneMuelles : public Scene
{
public:
	SceneMuelles();

	virtual ~SceneMuelles();

	virtual void Update(float t);

	virtual void initScene() {};

	virtual void keyPress(unsigned char key, const PxTransform& camera);
private:
	ParticleSystem* anchor;
	ParticleSystem* particleAttached;
	ParticleSystem* slinkyParticles;
	Particle* p1;
	Particle* p2;
	Particle* p3;
	SpringJoinParticles* p2_SJP;
	SpringJoinParticles* p3_SJP;
};

