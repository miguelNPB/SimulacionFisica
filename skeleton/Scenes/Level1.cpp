#include "Level1.h"
#include <iostream>
#include <chrono>
#include <random>

Level1::Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam) 
	: SceneRB(gScene, gPhysics), cam(cam){
	
	
}

Level1::~Level1() {

	
}

void Level1::initScene() {

	player = new RB_dynamic(this, "player");

	player->getRigidBody()->setGlobalPose(PxTransform(spawnPoint));


	cam->setPos(player->getPos().p + Vector3(0, 0, -10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());

	makeLevel();
	createParticleGenerators();
}

void Level1::createParticleGenerators() {
	lavaAnimSystem = new ParticleSystem(Vector3(0, 0, 0));
	lavaAnimGenerator = new CustomParticleGenerator(lavaAnimSystem, 0.01,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());

			float speed = 3;

			Vector3 initPos = player->getPos().p + Vector3(0, 5, 0);

			std::uniform_real_distribution<float>dist1(-1, 1);
			Vector3 randomDir = Vector3(dist1(gen), 0.7, dist1(gen));
			std::uniform_real_distribution<float>dist2(0.4, 1);
			Vector4 randomColor = Vector4(dist2(gen), 0, 0, 1);

			randomDir.normalize();
			Particle* p = new Particle(initPos, randomDir * speed,
				physx::PxGeometryType::eSPHERE, 0.15, 1,
				randomColor);

			return p;
		});
	lavaAnimSystem->setDestroyConditionTimer(0.5);
	lavaAnimGenerator->toggleActive();
}

void Level1::makeLevel() {
	deathFloor = new RB_static(this, "death", Vector3(0, -10, 0), cube, Vector3(500, 1, 500), DEATH_COLOR);
	goal = new RB_static(this, "goal", Vector3(0, 0, 500), cube, Vector3(5, 100, 5), GOAL_COLOR);
	spawn = new RB_static(this, "spawn", Vector3(0, -9, 0), cube, Vector3(5, 10, 5), SPAWN_COLOR);
	

	RB_static* level1 = new RB_static(this, "floor1", Vector3(0, 0, 20), cube, Vector3(2, 1, 15), FLOOR_COLOR);
	RB_static* level2 = new RB_static(this, "floor2", Vector3(0, 0, 35), cube, Vector3(10, 1, 2), FLOOR_COLOR);
	RB_static* level3 = new RB_static(this, "wall1", Vector3(0,3,38), cube, Vector3(10, 3, 1), WALL_COLOR);
	RB_static* level4 = new RB_static(this, "floor3_izq", Vector3(-12, 0, 43), cube, Vector3(2, 1, 10), FLOOR_COLOR);
	RB_static* level5 = new RB_static(this, "floor4_der", Vector3(12, 0, 43), cube, Vector3(2, 1, 10), FLOOR_COLOR);

	
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

			lavaAnimGenerator->toggleActive();
		}
	}

	lavaAnimSystem->update(t);
	lavaAnimGenerator->update(t);

	CameraMovement();
}

void Level1::keyPress(unsigned char key) {

	Vector3 cam_dir = cam->getDir();
	cam_dir.normalize();
	//std::cout << "X:" << cam_dir.x << " Y:" << cam_dir.y << " Z:" << cam_dir.z << "\n";
	
	

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
		player->getRigidBody()->addForce(totalForce * speed, physx::PxForceMode::);
	}

}

void Level1::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	if ((actor1->getName() == "player" && actor2->getName() == "death") ||
		(actor2->getName() == "player" && actor1->getName() == "death")) {
		kill = true;
		if (!startKillTimer) {
			startKillTimer = true;
			killTimerEnd = std::chrono::steady_clock::now() + std::chrono::milliseconds(KILL_ANIM_TIME);
			lavaAnimGenerator->toggleActive();
		}
	}
}

void Level1::CameraMovement() {
	cam->updateFollow(player->getPos());
}