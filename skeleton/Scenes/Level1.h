#pragma once
#include "SceneRB.h"
#include "../Rigidbody/RB_static.h"
#include "../Rigidbody/RB_dynamic.h"
#include "../P_Generators/CustomParticleGenerator.h"
#include "../F_Generators/RB_WindGenerator.h"
#include "../F_Generators/WindGenerator.h"
#include "../F_Generators/RB_SpringAnchorGenerator.h"
#include "../F_Generators/GravityGenerator.h"
#include "../F_Generators/RB_WhirlWind.h"
#include "../F_Generators/WhirlwindGenerator.h"

using namespace physx;

class Level1 : public SceneRB
{
public:
	Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam);

	~Level1();

	virtual void initScene() override;

	virtual void Update(float t) override;

	virtual void keyPress(unsigned char key) override;

	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
private:
	void CameraMovement();

	void initViento();
	void initLavaAnimation();
	void initDeathAnimation();
	void initMuelle();
	void initWhirlwind();
	void makeLevel();

	void killPlayer();

	Camera* cam;

	std::shared_ptr<RB_dynamic> player;
	float speed = 200;

	// ANIMACION LAVA
	ParticleSystem* lava_system;
	CustomParticleGenerator* lava_generator;

	// ANIMACION AL MORIR
	ParticleSystem* death_anim_system;
	CustomParticleGenerator* death_anim_generator;
	std::chrono::steady_clock::time_point kill_timer;
	std::chrono::steady_clock::time_point kill_timer_end;
	const int KILL_ANIM_TIME = 2000;
	bool kill = false;
	bool start_kill_timer = false;

	// VIENTO
	Vector3 viento1_pos = Vector3(0,0,20);
	float viento1_radius = 10;
	RB_WindGenerator* viento1_rbfgen;
	ParticleSystem* viento1_psys;
	CustomParticleGenerator* viento1_pgen;
	WindGenerator* viento1_fgen;
 
	// MUELLES
	RB_System* muelle1_system;
	RB_System* muelle2_system;
	Vector3 muelle1_pos = Vector3(0, 16, 60);
	Vector3 muelle2_pos = Vector3(0, 16, 80);

	// REMOLINO
	ParticleSystem* whirlwind_psys;
	CustomParticleGenerator* whirlwind_pgen;
	float whirlwind_radius = 9;
	Vector3 whirlwind_pos = Vector3(0, 5, 95);
	float whirlwhind_strength = 2;

	// SISTEMAS RB
	RB_System* global_system;
	RB_System* player_system;

	// PLATAFORMAS CLAVE NIVEL
	RB_static* death_floor;
	RB_static* goal;
	RB_static* spawn;

	// DELAY ENTRE ACTUALIZACIÓN DE FUERZA DEL PLAYER
	const float PLAYER_FORCE_INTERVAL = 0.1f;
	std::chrono::steady_clock::time_point lastForceUpdate;

	// SPAWNPOINT
	Vector3 spawnPoint = Vector3(0, 3, 84);

	// COLORES
	Vector4 DEATH_COLOR = Vector4(1, 0, 0, 1);
	Vector4 FLOOR_COLOR = Vector4(0, 0, 1, 1);
	Vector4 WALL_COLOR = Vector4(0, 0, 0.7, 1);
	Vector4 SPAWN_COLOR = Vector4(0.5, 0.5, 0.5, 1);
	Vector4 GOAL_COLOR = Vector4(0, 1, 0, 1);
};

