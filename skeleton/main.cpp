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


// crea los generadores de la P2
void create_P2() {
	/*
	// Crea bolas azules que suben y se autodestruyen a los 3 segundos.
	// Todos los valores aleatorios son sacados con una distribucion normal
	// de media 0.5 y desviacion tipica 0.2, que luego se mapean con los valores
	// minimos y maximos
	generatorPompas = new ParticleSystem({ 0, 25, 0 });
	generatorPompas->addParticleGenerator(new GeneratorNormal(generatorPompas,
		physx::PxGeometryType::eSPHERE, 0.1, // shape y tiempo de spawn
		0.5, 0.2, // media y desvTipica
		{ 1, 1, 1 }, { -1,1,-1 }, // min Dir y max Der
		10, 10, // min Speed y max Speed 
		1, 1, // min Size y max Size
		1, 1, // min mass y max mass
		{ 0,1,1,1 }, { 1,1,1,1 })); // min Color y max Color
	generatorPompas->setDestroyConditionTimer(3);

	// Crea bolas rojas de color variado de forma uniforme a cualquier
	// direccion del eje Z. Se eliminan cuando alcanzan el borde del 
	// circulo imaginario de radio 5. Todos los valores aleatorios son sacados
	// con una distribucion uniforme
	Vector3 solSpawnPoint = { 20, 25, 0 };
	generatorSol = new ParticleSystem(solSpawnPoint);
	generatorSol->addParticleGenerator(new GeneratorUniforme(generatorSol,
		physx::PxGeometryType::eSPHERE, 0.005,
		{ -1, -1, 0 }, { 1, 1, 0 },
		5, 5,
		0.3, 0.3,
		1, 1,
		{ 0.5, 0, 0, 1 }, { 1, 0, 0, 1 }));

	int radius = 5;
	generatorSol->setDestroyCondition([radius, solSpawnPoint](Particle* p) {
		Vector3 pTr = p->getTransform().p;
		double distancia = sqrt((pow(pTr.x - solSpawnPoint.x, 2) + pow(pTr.y - solSpawnPoint.y, 2)));
		return distancia > radius;
		});

	// Lanza cubos de color aleatorio hacia el eje Z positivo. Les
	// pone una velocidad aleatoria y están afectados por la gravedad,
	// su tamaño tambien es aleatorio y mueren al llegar al suelo (y < 0) 
	// Todos los valores aleatorios son sacados con una distribucion uniforme
	generatorCuboMulticolor = new ParticleSystem({ 0, 25, 10 });

	//generatorCuboMulticolor->ToggleGravity();

	generatorCuboMulticolor->addParticleGenerator(new GeneratorUniforme(generatorCuboMulticolor,
		physx::PxGeometryType::eBOX, 0.1,
		{ 0, 0, 1 }, { 0, 0, 1 },
		10, 30,
		0.1, 2,
		1, 1,
		{ 0,0,0,1 }, { 1,1,1,1 }));
	generatorCuboMulticolor->setDestroyCondition([](Particle* p) {
		return p->getTransform().p.y < 0;
		});
	*/
}


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

	currentScene = new SceneFloating();
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

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

	currentScene->keyPress(toupper(key), camera);

	switch(toupper(key))
	{
	case '1': 
		switchScene(new SceneWind());
		break;
	case '2':
		switchScene(new SceneWhirlwind());
		break;
	case '3':
		switchScene(new SceneExplosion());
		break;
	case '4':
		switchScene(new SceneMuelles());
		break;
	case '5':
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
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
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