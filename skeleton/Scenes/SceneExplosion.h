#pragma once
#include "Scene.h"
#include <random>
#include "../ParticleSystem.h"
#include "../P_Generators/CustomParticleGenerator.h"
#include "../F_Generators/ExplosionGenerator.h"

class SceneExplosion : public Scene
{
public:
	SceneExplosion();

	virtual ~SceneExplosion();

	virtual void initScene() {};

	virtual void Update(float t);

	virtual void keyPress(unsigned char key);
private:
	ParticleSystem* partSystem = nullptr;
	ExplosionGenerator* explosion = nullptr;
};