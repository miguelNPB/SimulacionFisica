#include "RB_Generator.h"

RB_Generator::RB_Generator(RB_System* sys, int spawnDelay, std::function<std::shared_ptr<RB>()> func) {
	addRbSystem(sys);
	this->startPoint = std::chrono::high_resolution_clock::now();
	this->spawnDelay = spawnDelay;
	this->func = func;
}

void RB_Generator::SpawnRigidbody() {
	for (auto sys : systems)
		sys->addRB(func());
}

void RB_Generator::update() {
	TimePoint now = std::chrono::high_resolution_clock::now();

	if (now > startPoint) {

		SpawnRigidbody();

		startPoint = (std::chrono::high_resolution_clock::now() + 
			std::chrono::milliseconds(spawnDelay));
	}
}

void RB_Generator::addRbSystem(RB_System* sys) {
	systems.push_back(sys);
}