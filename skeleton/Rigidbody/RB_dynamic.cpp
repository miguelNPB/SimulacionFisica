#include "RB_dynamic.h"

RB_dynamic::RB_dynamic(SceneRB* scene, const char* name, const Vector3& initPos,
	const Vector3& vel, double mass,
	ShapeType shapeType, const Vector3& size, const Vector4& color,
	PxMaterial* mat)
		: RB() {

	this->rigid = scene->get_gPhysics()->createRigidDynamic(PxTransform(initPos));
	this->rigid->setName(name);

	PxShape* shape = RB::GenerateShape(shapeType, size, mat);
	rigid->attachShape(*shape);
	scene->get_gScene()->addActor(*rigid);

	item = new RenderItem(shape, rigid, color);

	rigid->setLinearVelocity(vel);
	rigid->setAngularVelocity({ 0,0,0 });
	rigid->setMass(mass);

	//PxRigidBodyExt::updateMassAndInertia(*rigid, 0.15);
}

RB_dynamic::~RB_dynamic() {
	DeregisterRenderItem(item);
}