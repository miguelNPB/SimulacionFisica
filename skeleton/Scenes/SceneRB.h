#pragma once
#include "Scene.h"

using namespace physx;

class SceneRB : public Scene
{
public:
	SceneRB(PxScene* gScene, PxPhysics* gPhysics) {
		this->gScene = gScene;
		this->gPhysics = gPhysics;
	};

	virtual void Update(float t) {};
protected:
	PxScene* gScene = NULL;
	PxPhysics* gPhysics = NULL;
};