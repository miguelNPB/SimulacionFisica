#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_dynamic : public RB
{
public:
	RB_dynamic(SceneRB* scene, const Vector3& initPos, 
		const Vector3& vel, double mass, const Vector3& inertia, 
		ShapeType shape, const Vector3& size, const Vector4& color,
		PxMaterial* mat);

	RB_dynamic(SceneRB* scene, const Vector3& initPos,
		const Vector3& vel, double mass, const Vector3& inertia,
		ShapeType shape, float size, const Vector4& color,
		PxMaterial* mat) 
	{
		RB_dynamic(scene, initPos,vel, mass, inertia, shape, Vector3(size, size, size), color, mat);
	}

	PxRigidDynamic* getRigidBody() { return rigid; }
private:
	PxRigidDynamic* rigid = nullptr;
	SceneRB* scene;
};