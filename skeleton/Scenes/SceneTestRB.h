#pragma once
#include "SceneRB.h"

class SceneTestRB : public SceneRB
{
public:
	SceneTestRB(PxScene* gScene, PxPhysics* gPhysics);

	~SceneTestRB();

	virtual void Update(float t) override;
private:
};