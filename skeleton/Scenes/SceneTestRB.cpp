#include "SceneTestRB.h"
#include <random>
#include <iostream>

SceneTestRB::SceneTestRB(PxScene* gScene, PxPhysics* gPhysics)
	: SceneRB(gScene, gPhysics) {

	RB_static* stat = new RB_static(this, Vector3(20,50,0), sphere, 5, Vector4(1,1,1,1));


	normal = gScene->getPhysics().createMaterial(0.5, 0.5, 0.5);
	camaElastica = gScene->getPhysics().createMaterial(0.5, 0.5, 1);

	dyn1 = new RB_dynamic(this, Vector3(-20, 50, 0), Vector3(0, 0, 0),
		13.0, sphere, Vector3(5,0,0), Vector4(0, 1, 0, 0), normal);

	dyn2 = new RB_dynamic(this, Vector3(-20, 50, 20), Vector3(0, 0, 0),
		13.0, sphere, Vector3(5, 0, 0), Vector4(1, 0, 0, 0), camaElastica);

	RB_static* wall = new RB_static(this, Vector3(0, 20, -100), cube, Vector3(20,20,3), Vector4(1, 1, 1, 1));

	globalSystem = new RB_System();
	addSystem(globalSystem);

	addGenerator(new RB_Generator(globalSystem, 1000,[this]() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float>dist(1, 10);

		float pesoRnd = dist(gen);
		float color = (float)pesoRnd / 10;

		std::shared_ptr<RB> rb = std::make_shared<RB_dynamic>(this, Vector3(0,50,0),
			Vector3(0,0,0), pesoRnd * 10, sphere,
			Vector3(1, 0, 0), Vector4(0,0, 1 - color, 1), normal);

		return rb;
		}));

	globalSystem->addForceGenerator(new RB_WindGenerator(globalSystem, Vector3(0,0,0), 
		Vector3(0,0,1), 30, 1005));

	createGround();
}

void SceneTestRB::initScene() {

}

SceneTestRB::~SceneTestRB() {

}

void SceneTestRB::Update(float t) {
	SceneRB::Update(t);

}