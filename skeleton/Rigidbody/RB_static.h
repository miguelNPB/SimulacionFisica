#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_static : public RB
{
public:
	RB_static(SceneRB* scene, const Vector3& initPos, ShapeType shape, Vector3 size, Vector4 color);
	RB_static(SceneRB* scene, const Vector3& initPos, ShapeType shape, float size, Vector4 color) {
		RB_static(scene, initPos, shape, Vector3(size, size, size), color);
	}

	PxRigidStatic* getRigidBody() { return rigid; }
private:
	PxRigidStatic* rigid;

	PxTransform pos;
	SceneRB* scene;
};

