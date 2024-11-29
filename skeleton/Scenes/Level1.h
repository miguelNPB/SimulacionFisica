#pragma once
#include "SceneRB.h"
#include "../Rigidbody/RB_static.h"
#include "../Rigidbody/RB_dynamic.h"

class Level1 : public SceneRB
{
public:
	Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam);

	~Level1();

	virtual void initScene() override;

	virtual void Update(float t) override;
private:
	void CameraMovement();

	Camera* cam;

	RB_dynamic* player;

	RB_System* globalSystem;


};

