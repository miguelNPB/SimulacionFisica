#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_dynamic : public RB
{
public:
	RB_dynamic(SceneRB* scene, const char* name, const Vector3& initPos = Vector3(0, 0, 0),
		const Vector3& vel = Vector3(0, 0, 0), double mass = 1,
		ShapeType shapeType = sphere, const Vector3& size = Vector3(1, 1, 1), const Vector4& color = Vector4(1, 1, 1, 1),
		PxMaterial* mat = nullptr);

	virtual ~RB_dynamic();

	physx::PxTransform getPos() { return rigid->getGlobalPose(); }

	virtual PxRigidDynamic* getRigidBody() { return rigid; }

	virtual PxRigidActor* getActor() { return rigid; }
private:
	RenderItem* item;
	PxRigidDynamic* rigid;
	SceneRB* scene;
};