#include "SceneWhirlwind.h"

SceneWhirlwind::SceneWhirlwind() : Scene() {
	
	whirlwind = new ParticleSystem(Vector3(0, 0, 0));
	whirlwind->addParticleGenerator(new CustomParticleGenerator(whirlwind, 0.01,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(-1, 1);

			Vector3 particlePos = whirlwind->getOrigin() + Vector3(dist(gen), 0, dist(gen));

			return new Particle(particlePos, Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, 1,
				Vector4(1, 0, 1, 1));
		}));
	whirlwind->addForceGenerator(new WhirlwindGenerator(whirlwind, whirlwindRadius, 0, 5));
	whirlwind->setDestroyCondition([this](Particle* p) {
		Vector3 pTr = p->getTransform().p;
		float distancia = sqrt((pow(pTr.x - whirlwind->getOrigin().x, 2) + pow(pTr.y - whirlwind->getOrigin().y, 2) + pow(pTr.z - whirlwind->getOrigin().z, 2)));
		return distancia > whirlwindRadius;
		});
}

SceneWhirlwind::~SceneWhirlwind() {
	delete whirlwind;
}

void SceneWhirlwind::Update(float t) {
	whirlwind->update(t);
}