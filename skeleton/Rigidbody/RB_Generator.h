#pragma once
#include <functional>
#include "../RB_System.h"
#include <chrono>

class RB_Generator
{
public: 
	//spawndelay en milisegundos
	RB_Generator(RB_System* sys, int spawnDelay, std::function<std::shared_ptr<RB>()> func);

	void SpawnRigidbody();

	void update();

	void addRbSystem(RB_System* sys);
private:
	std::vector<RB_System*> systems;

	std::function<std::shared_ptr<RB>()> func;

	Vector3 origin;

	TimePoint startPoint;
	int spawnDelay;
};

