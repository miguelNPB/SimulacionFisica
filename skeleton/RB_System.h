#pragma once
#include "Rigidbody/RB.h"
#include <functional>
#include <memory>

class RB_ForceGenerator;

class RB_System
{
public:
	RB_System();

	~RB_System();

	void update(float t);

	// debe devolver TRUE si queremos que de destruyan
	void setDestroyCondition(std::function<bool(RB* p)> cond);
	// tiempo en milisegundos
	void setDestroyConditionTimer(int time);

	void addRB(std::shared_ptr<RB> rb);

	void addForceGenerator(RB_ForceGenerator* gen);

	std::vector<std::shared_ptr<RB>> getPool() { return pool; }
	
	void killAllRB();
private:
	void updateFGenerators(float t);

	Vector3 origin;

	std::vector<std::shared_ptr<RB>> pool;
	std::vector<RB_ForceGenerator*> fgen;
	std::function<bool(RB*)> destroyCondition;
};

