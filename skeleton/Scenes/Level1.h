#pragma once
#include "SceneRB.h"
#include "../Rigidbody/RB_static.h"
#include "../Rigidbody/RB_dynamic.h"

using namespace physx;

class Level1 : public SceneRB
{
public:
	Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam);

	~Level1();

	

	virtual void initScene() override;

	virtual void Update(float t) override;

	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;

	virtual void keyPress(unsigned char key) override;
private:
	void makeLevel();

	void killPlayer();

	void CameraMovement();
	Camera* cam;

	RB_dynamic* player;

	std::chrono::steady_clock::time_point killTimer;
	std::chrono::steady_clock::time_point killTimerEnd;
	const int KILL_ANIM_TIME = 2000;
	bool kill = false;
	bool startKillTimer = false;

	RB_static* deathFloor;
	RB_static* goal;
	RB_static* spawn;
	RB_System* globalSystem;

	Vector3 spawnPoint = Vector3(0, 3, 0);

	Vector4 DEATH_COLOR = Vector4(1, 0, 0, 1);
	Vector4 FLOOR_COLOR = Vector4(0, 0, 1, 1);
	Vector4 SPAWN_COLOR = Vector4(0.5, 0.5, 0.5, 1);
	Vector4 GOAL_COLOR = Vector4(0, 1, 0, 1);
};

