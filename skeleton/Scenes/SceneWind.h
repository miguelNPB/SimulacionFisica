#pragma once
#include "Scene.h"
#include <random>
#include "../ParticleSystem.h"
#include "../F_Generators/WindGenerator.h"
#include "../F_Generators/GravityGenerator.h"
#include "../P_Generators/CustomParticleGenerator.h"

class SceneWind : public Scene
{
public:
	SceneWind();

	virtual ~SceneWind();

	virtual void Update(float t);
private:
	ParticleSystem* partSystem;
};