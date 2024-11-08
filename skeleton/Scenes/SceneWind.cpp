#include "SceneWind.h"

SceneWind::SceneWind() : Scene() {
	createGround();
	createAxis();

	partSystem = new ParticleSystem({ 0, 50, 0 });
	partSystem->addParticleGenerator(new CustomParticleGenerator(partSystem, 0.05,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(1, 10);

			float pesoRnd = dist(gen);
			float color = (float)pesoRnd / 10;
			return new Particle(partSystem->getOrigin(), Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, pesoRnd,
				Vector4(1 - color, 1 - color, 1 - color, 1));
		}));
	partSystem->addForceGenerator(new GravityGenerator(partSystem, { 0,-1,0 }, GRAVITY));
	partSystem->addForceGenerator(new WindGenerator(partSystem, { -1, 0, 0 }, 50, 90));
	partSystem->setDestroyConditionTimer(3);
}

SceneWind::~SceneWind() {
	deleteGround();
	deleteAxis();

	delete partSystem;
}

void SceneWind::Update(float t) {
	partSystem->update(t);
}