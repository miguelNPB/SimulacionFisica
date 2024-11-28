#pragma once
#include "../RenderUtils.hpp"
#include <chrono>

using namespace physx;

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

enum ShapeType { cube, sphere };

class RB {
public:
	RB() {
		time = std::chrono::high_resolution_clock::now();
	}

	const TimePoint getStartTime() { return time; }
protected:
	TimePoint time;

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