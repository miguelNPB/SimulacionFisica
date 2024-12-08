#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_static : public RB
{
public:
	RB_static(SceneRB* scene, const char* name, const Vector3& initPos, ShapeType shape, Vector3 size, Vector4 color);

	virtual PxRigidDynamic* getRigidBody() { return nullptr; }

	//PxRigidStatic* getRigidBody() { return rigid; }
private:
	PxRigidStatic* rigid;

	PxTransform pos;
	SceneRB* scene;
};

