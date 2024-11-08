#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"

using namespace physx;

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Update(float t) = 0;

	virtual void keyPress(unsigned char key, const PxTransform& camera) { }

protected:
	void createGround() {
		groundTr = new PxTransform({ 0,0,0 });
		ground = new RenderItem(CreateShape(PxBoxGeometry(50, 0.1, 50)), groundTr, Vector4(0.2, 0.2, 0.2, 1));

		//RegisterRenderItem(ground);
	}

	void createAxis(float axisLength = 20, float axisSize = 2) {
		xAxisTr = new PxTransform({ axisLength,0,0 });
		xAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), xAxisTr, Vector4(1, 0, 0, 1));

		yAxisTr = new PxTransform({ 0,axisLength,0 });
		yAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), yAxisTr, Vector4(0, 1, 0, 1));

		zAxisTr = new PxTransform({ 0,0,axisLength });
		zAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), zAxisTr, Vector4(0, 0, 1, 1));

		//RegisterRenderItem(xAxis);
		//RegisterRenderItem(yAxis);
		//RegisterRenderItem(zAxis);
	}

	void deleteAxis() {
		DeregisterRenderItem(xAxis);
		DeregisterRenderItem(yAxis);
		DeregisterRenderItem(zAxis);
		/*
		delete xAxis;
		xAxis = nullptr;
		delete yAxis;
		yAxis = nullptr;
		delete zAxis;
		zAxis = nullptr;
		*/
	}

	void deleteGround() {
		DeregisterRenderItem(ground);
		/*
		delete ground;
		ground = nullptr;
		*/
	}

private:
	RenderItem* xAxis;
	PxTransform* xAxisTr;
	RenderItem* yAxis;
	PxTransform* yAxisTr;
	RenderItem* zAxis;
	PxTransform* zAxisTr;
	RenderItem* ground;
	PxTransform* groundTr;
};