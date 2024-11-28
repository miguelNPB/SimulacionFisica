#pragma once
#include "RB.h"
#include "../Scenes/SceneRB.h"

class RB_dynamic : public RB
{
public:
	RB_dynamic(SceneRB* scene, const Vector3& initPos, 
		const Vector3& vel, double mass, 
		ShapeType shape, const Vector3& size, const Vector4& color,
		PxMaterial* mat);

	RB_dynamic(SceneRB* scene, const Vector3& initPos,
		const Vector3& vel, double mass,
		ShapeType shape, float size, const Vector4& color,
		PxMaterial* mat);

	virtual PxRigidDynamic* getRigidBody() { return rigid; }

	int a = 0;
private:
	PxRigidDynamic* rigid;
	SceneRB* scene;
};