#pragma once
#include "SceneRB.h"
#include "../Rigidbody/RB_static.h"
#include "../Rigidbody/RB_dynamic.h"
#include "../F_Generators/RB_WindGenerator.h"

class SceneTestRB : public SceneRB
{
public:
	SceneTestRB(PxScene* gScene, PxPhysics* gPhysics);

	~SceneTestRB();

	virtual void initScene() override;

	virtual void Update(float t) override;
private:
	RB_System* globalSystem;

	PxMaterial* normal;
	PxMaterial* camaElastica;

	RB_dynamic* dyn1;
	RB_dynamic* dyn2;
};