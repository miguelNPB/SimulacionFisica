#include "RB_System.h"
#include "F_Generators/RB_ForceGenerator.h"

RB_System::RB_System() {

}

RB_System::~RB_System() {

}

void RB_System::update(float t) {
	updateFGenerators(t);
}

void RB_System::setDestroyCondition(std::function<bool(RB* p)> cond) {
	destroyCondition = cond;
}

void RB_System::setDestroyConditionTimer(int time) {
	setDestroyCondition([this, time](RB* rb) {
		return (rb->getStartTime() > 
			(std::chrono::high_resolution_clock::now() + 
				std::chrono::milliseconds(time)));
		});
}

void RB_System::addRB(std::shared_ptr<RB> rb) {
	pool.push_back(rb);
}

void RB_System::addForceGenerator(RB_ForceGenerator* gen) {
	fgen.push_back(gen);
}

void RB_System::killAllRB() {

}

void RB_System::updateFGenerators(float t) {
	for (auto gen : fgen)
		gen->update(t);
}
