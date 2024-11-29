#include "Level1.h"

Level1::Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam) 
	: SceneRB(gScene, gPhysics), cam(cam){
	
	player = new RB_dynamic(this);

	player->getRigidBody()->setGlobalPose(PxTransform(Vector3(0,50,0)));

	createGround();
}

Level1::~Level1() {

	
}

void Level1::initScene() {

}

void Level1::Update(float t) {
	
	CameraMovement();
}

void Level1::CameraMovement() {

	cam->setPos(player->getPos().p + Vector3(50, 50, 0));
	cam->lookAt(player->getRigidBody()->getGlobalPose());
}