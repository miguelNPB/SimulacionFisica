#include "SceneMuelles.h"

SceneMuelles::SceneMuelles() {
	//createGround();

	anchor = new ParticleSystem(Vector3(0,50,0));

	anchor->AddParticle(new Particle(anchor->getOrigin() + Vector3(0,0,0),Vector3(0,0,0),
		physx::PxGeometryType::eBOX, 1, 1, Vector4(0,0,0,1)));
	
	float distanceFromAnchor = 10;
	float elasticity = 3;
	particleAttached = new ParticleSystem(anchor->getOrigin());
	p1 = new Particle(particleAttached->getOrigin() + Vector3(0, -distanceFromAnchor, 0), Vector3(0, 0, 0),
		physx::PxGeometryType::eSPHERE, 3, 1, Vector4(1, 0, 0, 1));
	particleAttached->AddParticle(p1);
	particleAttached->addForceGenerator(new SpringAnchorGenerator(particleAttached, elasticity, distanceFromAnchor));
	particleAttached->addForceGenerator(new GravityGenerator(particleAttached, Vector3(0,-1,0), GRAVITY));

	slinkyParticles = new ParticleSystem(Vector3(0,0,0));
	slinkyParticles->addForceGenerator(new GravityGenerator(slinkyParticles, Vector3(0, -1, 0), GRAVITY));
	int offsetSlinky = 10;

	p2 = new Particle(particleAttached->getOrigin() + Vector3(0, -distanceFromAnchor - offsetSlinky, 0), Vector3(0, 0, 0),
		physx::PxGeometryType::eSPHERE, 3, 1, Vector4(0.6, 0, 0, 1));
	p2_SJP = new SpringJoinParticles(p2, p1, elasticity * 2, offsetSlinky);
	slinkyParticles->AddParticle(p2);

	p3 = new Particle(particleAttached->getOrigin() + Vector3(0, -distanceFromAnchor - offsetSlinky * 2, 0), Vector3(0, 0, 0),
		physx::PxGeometryType::eSPHERE, 3, 1, Vector4(0.35, 0, 0, 1));
	p3_SJP = new SpringJoinParticles(p3, p2, elasticity * 3, offsetSlinky);
	slinkyParticles->AddParticle(p3);
}

SceneMuelles::~SceneMuelles() {
	//deleteGround();

	delete anchor;
	delete particleAttached;
}

void SceneMuelles::Update(float t) {
	particleAttached->update(t);
	slinkyParticles->update(t);
	p2_SJP->update(t);
	p3_SJP->update(t);
}

void SceneMuelles::keyPress(unsigned char key, const PxTransform& cam) {

}