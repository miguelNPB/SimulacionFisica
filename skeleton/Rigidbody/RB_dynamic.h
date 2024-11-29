#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_dynamic : public RB
{
public:
	RB_dynamic(SceneRB* scene, const Vector3& initPos = Vector3(0, 0, 0),
		const Vector3& vel = Vector3(0, 0, 0), double mass = 1,
		ShapeType shapeType = sphere, const Vector3& size = Vector3(1, 1, 1), const Vector4& color = Vector4(1, 1, 1, 1),
		PxMaterial* mat = nullptr);

	physx::PxTransform getPos() { return rigid->getGlobalPose(); }

	virtual PxRigidDynamic* getRigidBody() { return rigid; }
private:
	PxRigidDynamic* rigid;
	SceneRB* scene;
};