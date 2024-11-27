#include "RB_static.h"

RB_static::RB_static(SceneRB* scene, const Vector3& initPos, ShapeType shape, Vector3 size, Vector4 color) {
	this->scene = scene;

	pos = PxTransform(initPos.x, initPos.y, initPos.z);
	rigid = scene->get_gPhysics()->createRigidStatic(pos);
	
	PxShape* geo = RB::GenerateShape(shape, size);
	rigid->attachShape(*geo);
	scene->get_gScene()->addActor(*rigid);

	RenderItem* item = new RenderItem(geo, rigid, color);
}