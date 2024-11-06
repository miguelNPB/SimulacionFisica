#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <random>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
//#include "CheckML.h"

#include "Particle.h"
#include "Proyectile.h"
#include "ProyectilePool.h"
#include "ParticleSystem.h"

#include "GeneratorNormal.h"
#include "GeneratorUniforme.h"
#include "CustomParticleGenerator.h"

#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"

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
float axisLength = 20;
float axisSize = 2;
RenderItem* xAxis;
PxTransform* xAxisTr;
RenderItem* yAxis;
PxTransform* yAxisTr;
RenderItem* zAxis;
PxTransform* zAxisTr;
RenderItem* ground;
PxTransform* groundTr;

bool renderP1 = false;

Proyectile* p1;
ProyectilePool* pool;

ParticleSystem* generatorPompas = nullptr;
ParticleSystem* generatorSol = nullptr;
ParticleSystem* generatorCuboMulticolor = nullptr;

ParticleSystem* whirlwind = nullptr;

ParticleSystem* partSystem = nullptr;
ExplosionGenerator* explosion = nullptr;

void create_P3() {

	/*
	generatorPompas = new ParticleSystem({ 0, 50, 0 });
	generatorPompas->addParticleGenerator(new CustomParticleGenerator(generatorPompas, 0.05,
		[](){
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(1, 10);

			float pesoRnd = dist(gen);
			float color = (float)pesoRnd / 10;
			return new Particle(generatorPompas->getOrigin(), Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, pesoRnd,
				Vector4(1 - color,1 - color,1 - color,1));
		}));
	generatorPompas->addForceGenerator(new GravityGenerator(generatorPompas, { 0,-1,0 }, GRAVITY));
	generatorPompas->addForceGenerator(new WindGenerator(generatorPompas, { -1, 0, 0 }, 90));
	generatorPompas->setDestroyConditionTimer(3);
	*/

	/*
	float whirlwindRadius = 30;
	whirlwind = new ParticleSystem(Vector3(0, 0, 0));
	whirlwind->addParticleGenerator(new CustomParticleGenerator(whirlwind, 0.01, 
		[](){
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(-1, 1);

			Vector3 particlePos = whirlwind->getOrigin() + Vector3(dist(gen), 0, dist(gen));

			return new Particle(particlePos, Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, 1,
				Vector4(1, 0, 1, 1));
		}));
	whirlwind->addForceGenerator(new WhirlwindGenerator(whirlwind, whirlwindRadius, 0, 5));
	whirlwind->setDestroyCondition([whirlwindRadius](Particle* p) {
		Vector3 pTr = p->getTransform().p;
		float distancia = sqrt((pow(pTr.x - whirlwind->getOrigin().x, 2) + pow(pTr.y - whirlwind->getOrigin().y, 2) + pow(pTr.z - whirlwind->getOrigin().z, 2)));
		return distancia > whirlwindRadius;
		});
	*/

	partSystem = new ParticleSystem(Vector3(0, 25, 0));
	partSystem->addParticleGenerator(new CustomParticleGenerator(partSystem, 0.01,
		[]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float>dist(-10, 10);

			Vector3 particlePos = partSystem->getOrigin() + Vector3(dist(gen), dist(gen), dist(gen));

			return new Particle(particlePos, Vector3(0, 0, 0),
				physx::PxGeometryType::eSPHERE, 1, 1,
				Vector4(1, 0, 1, 1));
		}));
	explosion = new ExplosionGenerator(partSystem, 15, 10000, 1);
	partSystem->addForceGenerator(explosion);
	partSystem->setDestroyCondition([](Particle* p) {
		Vector3 pTr = p->getPosition();
		float distancia = sqrt((pow(pTr.x - partSystem->getOrigin().x, 2) + pow(pTr.y - partSystem->getOrigin().y, 2) + pow(pTr.z - partSystem->getOrigin().z, 2)));
		return distancia > 50;
		});
}

// crea los generadores de la P2
void create_P2() {
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
}

// crea suelo y axis
void create_P1() {
	renderP1 = true;

	xAxisTr = new PxTransform({ axisLength,0,0 });
	xAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), xAxisTr, Vector4(1, 0, 0, 1));

	yAxisTr = new PxTransform({ 0,axisLength,0 });
	yAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), yAxisTr, Vector4(0, 1, 0, 1));

	zAxisTr = new PxTransform({ 0,0,axisLength });
	zAxis = new RenderItem(CreateShape(PxSphereGeometry(axisSize)), zAxisTr, Vector4(0, 0, 1, 1));

	groundTr = new PxTransform({ 0,0,0 });
	ground = new RenderItem(CreateShape(PxBoxGeometry(50, 0.1, 50)), groundTr, Vector4(0.2, 0.2, 0.2, 1));

	RegisterRenderItem(xAxis);
	RegisterRenderItem(yAxis);
	RegisterRenderItem(zAxis);
	RegisterRenderItem(ground);
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

	//create_P1();

	//create_P2();

	create_P3();
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	if (generatorPompas != nullptr)
		generatorPompas->update(t);
	if (generatorSol != nullptr)
		generatorSol->update(t);
	if (generatorCuboMulticolor != nullptr)
		generatorCuboMulticolor->update(t);
	if (whirlwind != nullptr)
		whirlwind->update(t);
	if (partSystem != nullptr)
		partSystem->update(t);

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

	delete generatorPompas;
	delete generatorSol;
	delete generatorCuboMulticolor;
	delete whirlwind;
	delete partSystem;

	if (renderP1) {
		DeregisterRenderItem(xAxis);
		DeregisterRenderItem(yAxis);
		DeregisterRenderItem(zAxis);
		DeregisterRenderItem(ground);
	}

	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
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
	switch(toupper(key))
	{
	case '1': 
		pool->getProyectile(camera.p, camera.q.rotate(PxVec3(0, 0, -1)) * 100, 2, 
			0.3f, {0,0,1,1});
		break;
	case '2':
		pool->getProyectile(camera.p, camera.q.rotate(PxVec3(0, 0, -1)) * 100, 10,
			1, {0,1,0,1});
		break;
	case '3':
		pool->getProyectile(camera.p, camera.q.rotate(PxVec3(0, 0, -1)) * 100, 20,
			3, { 1,0,0,1 });
		break;
	case 'F':
		if (explosion != nullptr)
			explosion->explode();
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