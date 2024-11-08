#include "SceneFloating.h"

SceneFloating::SceneFloating() {
	water = new Particle(Vector3(0, 40, 0), Vector3(0, 0, 0),
		30, 0.1, 30,
		1, Vector4(0, 0, 1, 0.5));

	floatingSystem = new ParticleSystem(water->getPosition());
	floatingSystem->AddParticle(new Particle(floatingSystem->getOrigin() + Vector3(0, 0, 0),
		Vector3(0, 0, 0), physx::PxGeometryType::eSPHERE, 3, 1.5));
	floatingSystem->addForceGenerator(new FloatingGenerator(
		floatingSystem, water->getPosition().y, 1, 100));
	floatingSystem->addForceGenerator(new GravityGenerator(
		floatingSystem, Vector3(0, -1, 0), GRAVITY));
}

SceneFloating::~SceneFloating() {
	delete water;
	delete floatingSystem;
}

void SceneFloating::Update(float t) {
	floatingSystem->update(t);
}

void SceneFloating::keyPress(unsigned char key, const PxTransform& cam) {

}