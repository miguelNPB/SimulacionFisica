#include "Level1.h"
#include <iostream>

Level1::Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam) 
	: SceneRB(gScene, gPhysics), cam(cam){
	
	player = new RB_dynamic(this);

	player->getRigidBody()->setGlobalPose(PxTransform(Vector3(0,5,0)));

	floor = new RB_static(this, Vector3(0,0,0), cube, Vector3(50,2,50), Vector4(0.5,0.5,1,1));

	RB_static* north = new RB_static(this, Vector3(50, 0, 0), cube, Vector3(2, 10, 2), Vector4(1, 0, 0, 1));
	RB_static* south = new RB_static(this, Vector3(-50, 0, 0), cube, Vector3(2, 10, 2), Vector4(0, 0, 1, 1));
	RB_static* east = new RB_static(this, Vector3(0, 0, 50), cube, Vector3(2, 10, 2), Vector4(0, 1, 0, 1));
	RB_static* west = new RB_static(this, Vector3(0, 0, -50), cube, Vector3(2, 10, 2), Vector4(1, 1, 1, 1));

	cam->setPos(player->getPos().p + Vector3(10, 10, 10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());
}

Level1::~Level1() {

	
}

void Level1::initScene() {

}

void Level1::Update(float t) {
	
	CameraMovement();
}

void Level1::keyPress(unsigned char key) {

	Vector3 cam_dir = cam->getDir();
	cam_dir.normalize();
	std::cout << "X:" << cam_dir.x << " Y:" << cam_dir.y << " Z:" << cam_dir.z << "\n";
	
	float speed = 100;

	Vector3 totalForce = Vector3(0, 0, 0);
	// FORWARD BACKWARD MOVEMENT
	if (key == 'W')
		totalForce += Vector3(cam_dir.x, 0, cam_dir.z);
	else if (key == 'S')
		totalForce += Vector3(-cam_dir.x, 0, -cam_dir.z);

	// LEFT RIGHT MOVEMENT
	if (key == 'A')
		totalForce += Vector3(cam_dir.z, 0, -cam_dir.x);
	else if (key == 'D')
		totalForce += Vector3(-cam_dir.z, 0, cam_dir.x);


	if (!totalForce.isZero()) {
		totalForce.normalize(); // Normalizar para que siempre se mueva a la misma velocidad
		player->getRigidBody()->addForce(totalForce * speed);
	}

}

void Level1::CameraMovement() {
	cam->updateFollow(player->getPos());
}