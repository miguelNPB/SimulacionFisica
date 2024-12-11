#pragma once
#include "RB_ForceGenerator.h"

class RB_SpringAnchorGenerator : public RB_ForceGenerator
{
public:
	RB_SpringAnchorGenerator(RB_System* sysRef, Vector3 origin, float elasticity, float restingLength);

	virtual void applyForce(std::shared_ptr<RB> rb);
private:
	Vector3 origin;
	float elasticity;
	float restingLength;
};