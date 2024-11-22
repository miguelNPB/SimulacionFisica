#include "SceneTestRB.h"

SceneTestRB::SceneTestRB(PxScene* gScene, PxPhysics* gPhysics)
	: SceneRB(gScene, gPhysics) {

	PxTransform pose = PxTransform(0,0,0);
	PxRigidStatic* aux = gPhysics->createRigidStatic(pose);
	PxMaterial* mat = gPhysics->createMaterial(1, 1, 1);
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(50), *mat);

	aux->attachShape(*shape);

	gScene->addActor(*aux);
}

SceneTestRB::~SceneTestRB() {

}

void SceneTestRB::Update(float t) {

}