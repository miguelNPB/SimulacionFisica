#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"

ParticleSystem::ParticleSystem(Vector3 origin) {
	timer = 0;
	this->origin = origin;

	// default destroy condition (no mueren)
	setDestroyCondition([](Particle* p){
		return false;
		});

}


void ParticleSystem::update(double t) {
	updateTimer(t);
	updateGenerators(t);
	killParticles();
	updateParticles(t);
}

void ParticleSystem::setDestroyCondition(std::function<bool(Particle* p)> cond) {
	destroyCondition = cond;
}

void ParticleSystem::setDestroyConditionTimer(double time) {
	setDestroyCondition([this,time](Particle* p) {
			return (p->timeAlive > time);
		});
}

void ParticleSystem::addParticleGenerator(ParticleGenerator* pgen) {
	pGenerators.push_back(pgen);
}

void ParticleSystem::addForceGenerator(ForceGenerator* fgen) {
	fGenerators.push_back(fgen);
}

void ParticleSystem::AddParticle(Particle* p) {
	pool.push_back(p);
}

void ParticleSystem::killParticles() {
	for (auto it = pool.begin(); it < pool.end(); ) {
		if (destroyCondition(*it)) {
			delete* it;
			it = pool.erase(it);
		}
		else {
			++it;
		}
	}
}

void ParticleSystem::updateParticles(double t) {
	for (auto p : pool) {
		p->integrate(t);
	}
		
}

void ParticleSystem::updateGenerators(double t) {
	for (auto g : fGenerators) {
		g->update(t);
	}

	for (auto g : pGenerators) {
		g->update(t);
	}

}

void ParticleSystem::updateTimer(double t) {
	timer += t;
}