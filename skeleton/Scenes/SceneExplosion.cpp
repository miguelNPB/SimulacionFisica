#include "SceneExplosion.h"

SceneExplosion::SceneExplosion() : Scene() {
	partSystem = new ParticleSystem(Vector3(0, 25, 0));
	partSystem->addParticleGenerator(new CustomParticleGenerator(partSystem, 0.01,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(-10, 10);

			Vector3 particlePos = partSystem->getOrigin() + Vector3(dist(gen), dist(gen), dist(gen));

			return new Particle(particlePos, Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, 1,
				Vector4(1, 0, 1, 1));
		}));
	explosion = new ExplosionGenerator(partSystem, 15, 10000, 1);
	partSystem->addForceGenerator(explosion);
	partSystem->setDestroyCondition([this](Particle* p) {
		Vector3 pTr = p->getPosition();
		float distancia = sqrt((pow(pTr.x - partSystem->getOrigin().x, 2) + pow(pTr.y - partSystem->getOrigin().y, 2) + pow(pTr.z - partSystem->getOrigin().z, 2)));
		return distancia > 50;
		});
}

SceneExplosion::~SceneExplosion() {
	delete partSystem;
}

void SceneExplosion::Update(float t) {
	partSystem->update(t);
}

void SceneExplosion::keyPress(unsigned char key) {

	switch (key) {
		case 'F':
			explosion->explode();
			break;
	}
}