#pragma once
#include "RB_ForceGenerator.h"

class RB_WindGenerator : public RB_ForceGenerator
{
public:
	RB_WindGenerator(RB_System* sysRef, Vector3 pos,
		Vector3 direction, float radius, float strength);

	virtual void applyForce(std::shared_ptr<RB> rb);
private:
	Vector3 direction;
	float strength;
	float radius;

	PxTransform* tr;

	const Vector4 color = Vector4(0.741, 0.741, 0.741, 0.639);
};

