#include "Level1.h"
#include <iostream>
#include <chrono>

Level1::Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam) 
	: SceneRB(gScene, gPhysics), cam(cam){
	
	player = new RB_dynamic(this, "player");


	player->getRigidBody()->setGlobalPose(PxTransform(spawnPoint));


	cam->setPos(player->getPos().p + Vector3(0, 0, -10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());
}

Level1::~Level1() {

	
}

void Level1::initScene() {
	makeLevel();
}

void Level1::makeLevel() {
	deathFloor = new RB_static(this, "death", Vector3(0, -10, 0), cube, Vector3(500, 1, 500), DEATH_COLOR);
	goal = new RB_static(this, "goal", Vector3(0, 0, 500), cube, Vector3(5, 100, 5), GOAL_COLOR);
	spawn = new RB_static(this, "spawn", Vector3(0, -9, 0), cube, Vector3(5, 10, 5), SPAWN_COLOR);
	

	RB_static* level1 = new RB_static(this, "floor", Vector3(0, 0, 55), cube, Vector3(5, 1, 50), FLOOR_COLOR);


	/*
	RB_static* north = new RB_static(this, "death", Vector3(50, 0, 0), cube, Vector3(2, 10, 2), Vector4(1, 0, 0, 1));
	RB_static* south = new RB_static(this, "south", Vector3(-50, 0, 0), cube, Vector3(2, 10, 2), Vector4(0, 0, 1, 1));
	RB_static* east = new RB_static(this, "east",Vector3(0, 0, 50), cube, Vector3(2, 10, 2), Vector4(0, 1, 0, 1));
	RB_static* west = new RB_static(this, "west",Vector3(0, 0, -50), cube, Vector3(2, 10, 2), Vector4(1, 1, 1, 1));
	*/

	
}

void Level1::killPlayer() {
	player->getRigidBody()->setGlobalPose(PxTransform(spawnPoint));
	player->getRigidBody()->clearForce();
	player->getRigidBody()->clearTorque();
	player->getRigidBody()->setLinearVelocity(Vector3(0, 0, 0));
	player->getRigidBody()->setAngularVelocity(Vector3(0, 0, 0));
	cam->setPos(player->getPos().p + Vector3(0, 0, -10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());
}

void Level1::Update(float t) {
	
	if (kill) {
		player->getRigidBody()->clearForce();
		player->getRigidBody()->clearTorque();
		player->getRigidBody()->setLinearVelocity(Vector3(0, 0, 0));
		player->getRigidBody()->setAngularVelocity(Vector3(0, 0, 0));

		killTimer = std::chrono::steady_clock::now();

		if (killTimer > killTimerEnd) {
			kill = false;
			startKillTimer = false;
			killPlayer();
		}
	}

	CameraMovement();
}

void Level1::keyPress(unsigned char key) {

	Vector3 cam_dir = cam->getDir();
	cam_dir.normalize();
	//std::cout << "X:" << cam_dir.x << " Y:" << cam_dir.y << " Z:" << cam_dir.z << "\n";
	
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

void Level1::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	if ((actor1->getName() == "player" && actor2->getName() == "death") ||
		(actor2->getName() == "player" && actor1->getName() == "death")) {
		kill = true;
		if (!startKillTimer) {
			startKillTimer = true;
			killTimerEnd = std::chrono::steady_clock::now() + std::chrono::milliseconds(KILL_ANIM_TIME);
		}
	}
}

void Level1::CameraMovement() {
	cam->updateFollow(player->getPos());
}