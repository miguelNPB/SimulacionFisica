#include "RB_WhirlWind.h"

RB_WhirlWind::RB_WhirlWind(RB_System* sysRef, Vector3 origin, float radius, float height, float strength)
	: RB_ForceGenerator(sysRef) {
	this->origin = origin;
	this->radius = radius;
	this->height = height;
	this->strength = strength;

#ifdef DEBUG
	PxTransform* tr = new PxTransform(origin);
	PxShape* shape = CreateShape(PxSphereGeometry(radius));
	RenderItem* item = new RenderItem(shape, tr, Vector4(1,1,1,0));
#endif // DEBUG

}

void RB_WhirlWind::applyForce(std::shared_ptr<RB> rb) {

	if ((rb->getRigidBody()->getGlobalPose().p - origin).magnitudeSquared() < radius * radius)
	{
		Vector3 whirlwindVel = strength * Vector3(
			-(rb->getRigidBody()->getGlobalPose().p.z - origin.z),
			height - (rb->getRigidBody()->getGlobalPose().p.y - origin.y),
			rb->getRigidBody()->getGlobalPose().p.x - origin.x);

		rb->getRigidBody()->addForce(whirlwindVel);
	}
}