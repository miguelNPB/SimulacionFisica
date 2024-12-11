#pragma once
#include "RB_ForceGenerator.h"

class RB_WhirlWind : public RB_ForceGenerator
{
public:
	RB_WhirlWind(RB_System* sysRef, Vector3 origin, float radius, float height, float strength);

	virtual void applyForce(std::shared_ptr<RB> rb);
private:
	Vector3 origin;
	float radius;
	float height;
	float strength;
};

