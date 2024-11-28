#pragma once
#include "RB_ForceGenerator.h"

class RB_WindGenerator : public RB_ForceGenerator
{
public:
	RB_WindGenerator();

	virtual void applyForce(std::shared_ptr<RB>);
private:
};

