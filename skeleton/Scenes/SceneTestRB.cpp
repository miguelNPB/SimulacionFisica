#include "SceneTestRB.h"

SceneTestRB::SceneTestRB(PxScene* gScene, PxPhysics* gPhysics)
	: SceneRB(gScene, gPhysics) {

	RB_static* stat = new RB_static(this, Vector3(20,50,0), sphere, 5, Vector4(1,1,1,1));


	normal = gScene->getPhysics().createMaterial(0.5, 0.5, 0.5);
	camaElastica = gScene->getPhysics().createMaterial(0.5, 0.5, 1);

	dyn1 = new RB_dynamic(this, Vector3(-20, 50, 0), Vector3(0, 0, 0),
		3.0, Vector3(0,0,0), sphere, 5.0, Vector4(0, 1, 0, 0), normal);

	dyn2 = new RB_dynamic(this, Vector3(-20, 50, 20), Vector3(0, 0, 0),
		3.0, Vector3(0, 0, 0), sphere, 5.0, Vector4(1, 0, 0, 0), camaElastica);



	createGround();
}

void SceneTestRB::initScene() {

}

SceneTestRB::~SceneTestRB() {

}

void SceneTestRB::Update(float t) {

}