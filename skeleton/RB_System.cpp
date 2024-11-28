#include "RB_System.h"
#include "Rigidbody/RB.h"

RB_System::RB_System() {

}

RB_System::~RB_System() {

}

void RB_System::update(float t) {
	updateFGenerators();
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

void RB_System::addForceGenerator() {

}

void RB_System::killAllRB() {

}

void RB_System::updateFGenerators() {

}
