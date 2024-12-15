#pragma once
#include "Scene.h"
#include "../RigidBody/RB_Generator.h"
#include "../ParticleSystem.h"
#include "../P_Generators/ParticleGenerator.h"

using namespace physx;

class SceneRB : public Scene
{
public:
	SceneRB(PxScene* gScene, PxPhysics* gPhysics) {
		this->gScene = gScene;
		this->gPhysics = gPhysics;
	};

	virtual ~SceneRB() {
		for (auto sys : rb_systems) {
			sys->killAllRB();
		}
		rb_systems.clear();

		for (auto sys : p_systems) {
			delete sys;
		}
		p_systems.clear();

		rb_generators.clear();
		p_generators.clear();
	}

	virtual void createGround() override {
		PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({0,0,0}));
		PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
		suelo->attachShape(*shape);
		gScene->addActor(*suelo);

		RenderItem* item = new RenderItem(shape, suelo, { 0,0,0, 1 });
	}

	virtual void Update(float t) {
		for (auto sys : rb_systems)
			sys->update(t);

		for (auto gen : rb_generators)
			gen->update();

		for (auto sys : p_systems)
			sys->update(t);

		for (auto gen : p_generators)
			gen->update(t);
	};
	
	virtual void initScene() {};

	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override {};

	void addGenerator(RB_Generator* gen) {
		rb_generators.push_back(gen);
	}

	void removeGenerator(RB_Generator* gen) {
		auto it = std::find(rb_generators.begin(), rb_generators.end(), gen);

		// Si el elemento se encuentra, eliminarlo
		if (it != rb_generators.end()) {
			rb_generators.erase(it);
		}
	}

	void addGenerator(ParticleGenerator* gen) {
		p_generators.push_back(gen);
	}

	void removeGenerator(ParticleGenerator* gen) {
		auto it = std::find(p_generators.begin(), p_generators.end(), gen);

		// Si el elemento se encuentra, eliminarlo
		if (it != p_generators.end()) {
			p_generators.erase(it);
		}
	}

	void addSystem(RB_System* sys) {
		rb_systems.push_back(sys);
	}

	void removeSystem(RB_System* sys) {
		auto it = std::find(rb_systems.begin(), rb_systems.end(), sys);

		// Si el elemento se encuentra, eliminarlo
		if (it != rb_systems.end()) {
			rb_systems.erase(it);
		}
	}

	void addSystem(ParticleSystem* sys) {
		p_systems.push_back(sys);
	}

	void removeSystem(ParticleSystem* sys) {
		auto it = std::find(p_systems.begin(), p_systems.end(), sys);

		// Si el elemento se encuentra, eliminarlo
		if (it != p_systems.end()) {
			p_systems.erase(it);
		}
	}

	PxScene* get_gScene() { return gScene; }
	PxPhysics* get_gPhysics() { return gPhysics; }
protected:
	PxScene* gScene = NULL;
	PxPhysics* gPhysics = NULL;

	std::vector<RB_System*> rb_systems;
	std::vector<RB_Generator*> rb_generators;
	std::vector<ParticleSystem*> p_systems;
	std::vector<ParticleGenerator*> p_generators;
};