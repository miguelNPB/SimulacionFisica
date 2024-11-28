#pragma once
#include "../Rigidbody/RB.h"
#include "../RB_System.h"

class RB_ForceGenerator 
{
public:
	RB_ForceGenerator(RB_System* sysRef) {
		this->sysRef = sysRef;
	}

	virtual void applyForce(std::shared_ptr<RB>) = 0;

	virtual void update(float t) {
		for (auto rb : sysRef->getPool())
			applyForce(rb);
	}
protected:
	RB_System* sysRef;
};