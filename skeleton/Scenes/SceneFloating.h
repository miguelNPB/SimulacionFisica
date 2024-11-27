#pragma once
#include "Scene.h"
#include "../ParticleSystem.h"
#include "../F_Generators/FloatingGenerator.h"
#include "../F_Generators/GravityGenerator.h"

class SceneFloating : public Scene
{
public:
	SceneFloating();

	virtual ~SceneFloating();

	virtual void initScene() {};

	virtual void Update(float t);

	virtual void keyPress(unsigned char key, const PxTransform& camera);
private:
	Particle* water;
	ParticleSystem* floatingSystem;
};

