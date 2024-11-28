#pragma once
#include "Scene.h"
#include "../RigidBody/RB_Generator.h"

using namespace physx;

class SceneRB : public Scene
{
public:
	SceneRB(PxScene* gScene, PxPhysics* gPhysics) {
		this->gScene = gScene;
		this->gPhysics = gPhysics;
	};

	virtual ~SceneRB() {

	}

	virtual void createGround() override {
		PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({0,0,0}));
		PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
		suelo->attachShape(*shape);
		gScene->addActor(*suelo);

		RenderItem* item = new RenderItem(shape, suelo, { 0,0,0, 1 });
	}

	virtual void Update(float t) {
		for (auto sys : systems)
			sys->update(t);

		for (auto gen : generators)
			gen->update();
	};
	
	virtual void initScene() {};

	void addGenerator(RB_Generator* gen) {
		generators.push_back(gen);
	}

	void removeGenerator(RB_Generator* gen) {
		auto it = std::find(generators.begin(), generators.end(), gen);

		// Si el elemento se encuentra, eliminarlo
		if (it != generators.end()) {
			generators.erase(it);
		}
	}

	void addSystem(RB_System* sys) {
		systems.push_back(sys);
	}

	void removeSystem(RB_System* sys) {
		auto it = std::find(systems.begin(), systems.end(), sys);

		// Si el elemento se encuentra, eliminarlo
		if (it != systems.end()) {
			systems.erase(it);
		}
	}

	PxScene* get_gScene() { return gScene; }
	PxPhysics* get_gPhysics() { return gPhysics; }
protected:
	PxScene* gScene = NULL;
	PxPhysics* gPhysics = NULL;

	std::vector<RB_Generator*> generators;
	std::vector<RB_System*> systems;
};