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

	virtual void createGround() override {
		PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({0,0,0}));
		PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
		suelo->attachShape(*shape);
		gScene->addActor(*suelo);

		RenderItem* item = new RenderItem(shape, suelo, { 0,0,0, 1 });
	}

	virtual void Update(float t) {};
	
	virtual void initScene() {};

	PxScene* get_gScene() { return gScene; }
	PxPhysics* get_gPhysics() { return gPhysics; }
protected:
	PxScene* gScene = NULL;
	PxPhysics* gPhysics = NULL;
};