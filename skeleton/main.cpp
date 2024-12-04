#include <ctype.h>


#include <vector>
#include <random>


#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
//#include "CheckML.h"

#include "Scenes/Scene.h"

#include "Scenes/SceneExplosion.h"
#include "Scenes/SceneWhirlwind.h"
#include "Scenes/SceneWind.h"
#include "Scenes/SceneMuelles.h"
#include "Scenes/SceneFloating.h"
#include "Scenes/SceneTestRB.h"

#include "Scenes/Level1.h"

std::string display_text = "This is a test";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

/// /// /// 

Scene* currentScene = nullptr;
bool init = false;

RenderItem* camFollowObject = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// // // // // // // // // 

	currentScene = new Level1(gScene, gPhysics, GetCamera());
	init = true;
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	if (init) {
		currentScene->initScene();
		init = false;
	}
	currentScene->Update(t);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();

	delete currentScene;

	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

void switchScene(Scene* newScene) {
	delete currentScene;
	currentScene = newScene;

	init = true;
}

float quaternionToPitch(const PxQuat& q) {
	// q = (w, x, y, z)
	float w = q.w;
	float x = q.x;
	float y = q.y;
	float z = q.z;

	// Calcular el ángulo de pitch (rotación sobre el eje X)
	float sinp = 2.0f * (w * x + y * z);
	float cosp = 1.0f - 2.0f * (x * x + y * y);
	float pitch = std::atan2(sinp, cosp);

	// Retornar el ángulo en grados
	return pitch;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	currentScene->keyPress(toupper(key));

	switch(toupper(key))
	{
	case '1':
		switchScene(new SceneRB(gScene, gPhysics));
		break;
	case '5': 
		switchScene(new SceneWind());
		break;
	case '6':
		switchScene(new SceneWhirlwind());
		break;
	case '7':
		switchScene(new SceneExplosion());
		break;
	case '8':
		switchScene(new SceneMuelles());
		break;
	case '9':
		switchScene(new SceneFloating());
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}

	
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	currentScene->onCollision(actor1, actor2);
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}