#include "RB_dynamic.h"

RB_dynamic::RB_dynamic(SceneRB* scene, const Vector3& initPos = Vector3(0, 0, 0),
	const Vector3& vel = Vector3(0,0,0), double mass = 1, const Vector3& inertia = Vector3(0, 0, 0),
	ShapeType shapeType = sphere, const Vector3& size = Vector3(1, 1, 1), const Vector4& color = Vector4(1, 1, 1, 1),
	PxMaterial* mat = nullptr){

	this->rigid = scene->get_gPhysics()->createRigidDynamic(PxTransform(initPos));

	PxShape* shape = RB::GenerateShape(shapeType, size, mat);
	rigid->attachShape(*shape);
	scene->get_gScene()->addActor(*rigid);

	RenderItem* item = new RenderItem(shape, rigid, color);

	rigid->setLinearVelocity(vel);
	rigid->setAngularVelocity({ 0,0,0 });
	rigid->setMass(mass);
	rigid->setMassSpaceInertiaTensor(inertia);

	PxRigidBodyExt::updateMassAndInertia(*rigid, 0.15);
}