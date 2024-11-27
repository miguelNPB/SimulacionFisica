#pragma once
#include "../RenderUtils.hpp"

using namespace physx;

enum ShapeType { cube, sphere };

class RB {
public:
	RB() {

	}
protected:
	PxShape* GenerateShape(ShapeType shape, Vector3 size, PxMaterial* mat = nullptr) {
		PxShape* geom;

		switch (shape) {
		case sphere:
			if (mat == nullptr)
				geom = CreateShape(PxSphereGeometry(size[0]));
			else
				geom = CreateShape(PxSphereGeometry(size[0]), mat);
			break;
		case cube:
			if (mat == nullptr)
				geom = CreateShape(PxBoxGeometry(size[0], size[1], size[2]));
			else
				geom = CreateShape(PxBoxGeometry(size[0], size[1], size[2]), mat);
			break;
		}

		return geom;
	}
};