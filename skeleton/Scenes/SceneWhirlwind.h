#pragma once
#include "Scene.h"
#include <random>
#include "../ParticleSystem.h"
#include "../P_Generators/CustomParticleGenerator.h"
#include "../F_Generators/WhirlwindGenerator.h"

class SceneWhirlwind : public Scene
{
public:
	SceneWhirlwind();

	virtual ~SceneWhirlwind();

	virtual void Update(float t);
private:
	float whirlwindRadius = 30;
	ParticleSystem* whirlwind = nullptr;
};

