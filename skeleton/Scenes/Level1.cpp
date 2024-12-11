#include "Level1.h"
#include <iostream>
#include <chrono>
#include <random>

Level1::Level1(PxScene* gScene, PxPhysics* gPhysics, Camera* cam) 
	: SceneRB(gScene, gPhysics), cam(cam){
	
	
}

Level1::~Level1() {

	
}

void Level1::initScene() {

	global_system = new RB_System();
	player_system = new RB_System();
	addSystem(global_system);
	addSystem(player_system);

	player = std::make_shared<RB_dynamic>(this, "player");
	player_system->addRB(player);
	player->getRigidBody()->setGlobalPose(PxTransform(spawnPoint));

	cam->setPos(player->getPos().p + Vector3(0, 0, -10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());

	makeLevel();
	initViento();
	initDeathAnimation();
	initLavaAnimation();
	initMuelle();
	initWhirlwind();
}

void Level1::Update(float t) {
	SceneRB::Update(t);

	if (kill) {
		player->getRigidBody()->clearForce();
		player->getRigidBody()->clearTorque();
		player->getRigidBody()->setLinearVelocity(Vector3(0, 0, 0));
		player->getRigidBody()->setAngularVelocity(Vector3(0, 0, 0));

		kill_timer = std::chrono::steady_clock::now();


		if (kill_timer > kill_timer_end) {
			kill = false;
			start_kill_timer = false;
			killPlayer();

			death_anim_generator->toggleActive();
		}
	}

	CameraMovement();
}

void Level1::keyPress(unsigned char key) {

	auto now = std::chrono::high_resolution_clock::now();
	float elapsedTime = std::chrono::duration<float>(now - lastForceUpdate).count();
	if (elapsedTime < PLAYER_FORCE_INTERVAL)
		return;

	lastForceUpdate = std::chrono::high_resolution_clock::now();
	
	Vector3 cam_dir = cam->getDir();
	cam_dir.normalize();
	//std::cout << "X:" << cam_dir.x << " Y:" << cam_dir.y << " Z:" << cam_dir.z << "\n";

	Vector3 totalForce = Vector3(0, 0, 0);
	// FORWARD BACKWARD MOVEMENT
	if (key == 'W')
		totalForce += Vector3(cam_dir.x, 0, cam_dir.z);
	else if (key == 'S')
		totalForce += Vector3(-cam_dir.x, 0, -cam_dir.z);

	// LEFT RIGHT MOVEMENT
	if (key == 'A')
		totalForce += Vector3(cam_dir.z, 0, -cam_dir.x);
	else if (key == 'D')
		totalForce += Vector3(-cam_dir.z, 0, cam_dir.x);


	if (!totalForce.isZero()) {
		totalForce.normalize(); // Normalizar para que siempre se mueva a la misma velocidad
		player->getRigidBody()->addForce(totalForce * speed);
	}

}

void Level1::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	if ((actor1->getName() == "player" && actor2->getName() == "death") ||
		(actor2->getName() == "player" && actor1->getName() == "death")) {
		kill = true;
		if (!start_kill_timer) {
			start_kill_timer = true;
			kill_timer_end = std::chrono::steady_clock::now() + std::chrono::milliseconds(KILL_ANIM_TIME);
			death_anim_generator->toggleActive();
		}
	}
}

void Level1::CameraMovement() {
	cam->updateFollow(player->getPos());
}

void Level1::initViento() {
	// PARTICLE SYSTEM Y GENERATOR
	viento1_psys = new ParticleSystem(viento1_pos);
	viento1_pgen = new CustomParticleGenerator(viento1_psys, 0.005,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());

			float speed = 6;

			// PONER LA POSICION EN LA PARTE IZQ DE LA ESFERA Y QUE VAYA PARA DERECHA
			std::uniform_real_distribution<float>dist_theta(physx::PxPi / 2, 3 * physx::PxPi / 2);
			float theta = dist_theta(gen);
			std::uniform_real_distribution<float>dist_phi(0, physx::PxPi);
			float phi = dist_phi(gen);
			Vector3 initPos = viento1_pos + Vector3(
				viento1_radius * sin(phi) * cos(theta),
				viento1_radius * sin(phi) * sin(theta),
				viento1_radius * cos(phi));


			//std::uniform_real_distribution<float>dist1(-1, 1);
			Vector3 randomDir = Vector3(1, 0, 0);
			std::uniform_real_distribution<float>dist2(0.4, 1);
			Vector4 randomColor = Vector4(0, 0, dist2(gen), 1);

			randomDir.normalize();
			Particle* p = new Particle(initPos, randomDir * speed,
				physx::PxGeometryType::eSPHERE, 0.15, 1,
				randomColor);

			return p;
		});

	viento1_psys->setDestroyCondition([this](Particle* p) {
		return std::abs(((p->getPosition() - viento1_pos).magnitude()) > viento1_radius * 1.05);
		});

	addGenerator(viento1_pgen);
	addSystem(viento1_psys);

	// FORCEGENERATOR
	viento1_rbfgen = new RB_WindGenerator(player_system, viento1_pos, Vector3(-1,0,0),
		viento1_radius,5);
	player_system->addForceGenerator(viento1_rbfgen);
}

void Level1::initLavaAnimation() {
	lava_system = new ParticleSystem(Vector3(0,0,0));

	lava_generator = new CustomParticleGenerator(lava_system, 0.01, 
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());

			float speed = 4;

			std::uniform_int_distribution<int> dist_pos_x(-50, 50);
			std::uniform_int_distribution<int> dist_pos_z(-50, 150);
			Vector3 initPos = Vector3(dist_pos_x(gen), 0, dist_pos_z(gen));



			std::uniform_real_distribution<float>dist_dir_x_z(-0.5, 0.5);
			Vector3 randomDir = Vector3(dist_dir_x_z(gen), 1, dist_dir_x_z(gen));
			randomDir.normalize();

			std::uniform_real_distribution<float>dist_mass(0.4, 1);
			float randomMass = dist_mass(gen);

			std::uniform_real_distribution<float>dist_color(0.4, 1);
			Vector4 randomColor = Vector4(dist_color(gen), 0, 0, 1);

			Particle* p = new Particle(initPos, randomDir * speed,
				physx::PxGeometryType::eSPHERE, randomMass / 5, randomMass,
				randomColor);

			return p;
		});
	lava_system->addForceGenerator(new GravityGenerator(lava_system, Vector3(0, -1, 0), GRAVITY));

	lava_system->setDestroyCondition([this](Particle* p) {
		return p->getPosition().y < -5;
		});
	addSystem(lava_system);
	addGenerator(lava_generator);
}

void Level1::initDeathAnimation() {
	// animacion muerte
	death_anim_system = new ParticleSystem(Vector3(0, 0, 0));
	death_anim_generator = new CustomParticleGenerator(death_anim_system, 0.01,
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());

			float speed = 3;

			Vector3 initPos = player->getPos().p + Vector3(0, 1, 0);

			std::uniform_real_distribution<float>dist1(-1, 1);
			Vector3 randomDir = Vector3(dist1(gen), 0.7, dist1(gen));
			std::uniform_real_distribution<float>dist2(0.4, 1);
			Vector4 randomColor = Vector4(dist2(gen), 0, 0, 1);

			randomDir.normalize();
			Particle* p = new Particle(initPos, randomDir * speed,
				physx::PxGeometryType::eSPHERE, 0.15, 1,
				randomColor);

			return p;
		});
	death_anim_system->setDestroyConditionTimer(0.5);
	death_anim_generator->toggleActive();

	addGenerator(death_anim_generator);
	addSystem(death_anim_system);
}

void Level1::initMuelle() {

	muelle1_system = new RB_System();
	addSystem(muelle1_system);
	
	std::shared_ptr<RB> muelle1 = std::make_shared<RB_dynamic>(this, "muelle1", Vector3(0,6,60),
		Vector3(0,0,0), 1, cube, Vector3(2,1,1), DEATH_COLOR);
	muelle1->getRigidBody()->setName("death");
	muelle1_system->addRB(muelle1);

	RB_SpringAnchorGenerator* muelle1_rbfgen = new RB_SpringAnchorGenerator(muelle1_system, 
		muelle1_pos, 1.3, 4);
	muelle1_system->addForceGenerator(muelle1_rbfgen);


	muelle2_system = new RB_System();
	addSystem(muelle2_system);

	std::shared_ptr<RB> muelle2 = std::make_shared<RB_dynamic>(this, "muelle2", Vector3(0,6,80),
		Vector3(0, 0, 0), 1, cube, Vector3(2, 1, 1), DEATH_COLOR);
	muelle2->getRigidBody()->setName("death");
	muelle2_system->addRB(muelle2);

	RB_SpringAnchorGenerator* muelle2_rbfgen = new RB_SpringAnchorGenerator(muelle2_system,
		muelle2_pos, 1.3, 4);
	muelle2_system->addForceGenerator(muelle2_rbfgen);
}

void Level1::initWhirlwind() {

	whirlwind_psys = new ParticleSystem(whirlwind_pos);
	whirlwind_pgen = new CustomParticleGenerator(whirlwind_psys, 0.003, 
		[this]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			
			std::uniform_real_distribution<float>dist_pos(-whirlwind_radius / 2.7, whirlwind_radius / 2.7);
			Vector3 randomPos = whirlwind_pos + Vector3(dist_pos(gen), -5, dist_pos(gen));

			std::uniform_real_distribution<float>dist_dir(-1, 1);
			Vector3 randomDir = Vector3(dist_dir(gen), 0, dist_dir(gen));

			std::uniform_real_distribution<float>dist_color(0.3, 1);
			Vector4 randomColor = Vector4(dist_color(gen), 0, dist_color(gen), 1.0);

			std::uniform_real_distribution<float>dist_size(0.1, 0.4);
			float randomSize = dist_size(gen);

			Particle* p = new Particle(randomPos, randomDir,
				physx::PxGeometryType::eSPHERE, randomSize, 2.5, 
				randomColor);

			return p;
		});

	WhirlwindGenerator* whirlwind_pfgen = new WhirlwindGenerator(whirlwind_psys,
		whirlwind_radius, 10, 6);

	whirlwind_psys->addForceGenerator(whirlwind_pfgen);
	whirlwind_psys->addForceGenerator(new GravityGenerator(
		whirlwind_psys, Vector3(0,-1,0), GRAVITY));

	whirlwind_psys->setDestroyCondition([this](Particle* p) {
		return std::abs(((p->getPosition() - whirlwind_pos).magnitude()) > whirlwind_radius * 1.1);
		});

	addSystem(whirlwind_psys);
	addGenerator(whirlwind_pgen);

	// RB FORCE GENERATOR
	RB_WhirlWind* whirlwind_rbfgen = new RB_WhirlWind(player_system, whirlwind_pos,
		whirlwind_radius, 5, whirlwhind_strength);
	player_system->addForceGenerator(whirlwind_rbfgen);
}

void Level1::makeLevel() {
	death_floor = new RB_static(this, "death", Vector3(0, -10, 0), cube, Vector3(500, 1, 500), DEATH_COLOR);
	goal = new RB_static(this, "goal", Vector3(0, 0, 130), cube, Vector3(5, 100, 5), GOAL_COLOR);
	spawn = new RB_static(this, "spawn", Vector3(0, -9, 0), cube, Vector3(5, 10, 5), SPAWN_COLOR);
	
	RB_static* level1 = new RB_static(this, "floor1", Vector3(0, 0, 20), cube, Vector3(2, 1, 15), FLOOR_COLOR);
	RB_static* level2 = new RB_static(this, "floor2", Vector3(0, 0, 35), cube, Vector3(10, 1, 2), FLOOR_COLOR);
	RB_static* level3 = new RB_static(this, "wall1", Vector3(0, 3, 38), cube, Vector3(10, 3, 1), WALL_COLOR);
	
	RB_static* level4 = new RB_static(this, "floor3_izq", Vector3(-12, 0, 43), cube, Vector3(2, 1, 10), FLOOR_COLOR);
	RB_static* level5 = new RB_static(this, "floor4_der", Vector3(12, 0, 43), cube, Vector3(2, 1, 10), FLOOR_COLOR);
	RB_static* level6 = new RB_static(this, "floor5", Vector3(0, 0, 51), cube, Vector3(10, 1, 2), FLOOR_COLOR);
	
	RB_static* level7 = new RB_static(this, "floor6", Vector3(0, 0, 66), cube, Vector3(2, 1, 15), FLOOR_COLOR);
	RB_static* level8 = new RB_static(this, "floor7", Vector3(0, 0, 95), cube, Vector3(14, 1, 14), FLOOR_COLOR);
	RB_static* level9 = new RB_static(this, "floor8", Vector3(0, 0, 118), cube, Vector3(2, 1, 10), FLOOR_COLOR);
}

void Level1::killPlayer() {
	player->getRigidBody()->setGlobalPose(PxTransform(spawnPoint));
	player->getRigidBody()->clearForce();
	player->getRigidBody()->clearTorque();
	player->getRigidBody()->setLinearVelocity(Vector3(0, 0, 0));
	player->getRigidBody()->setAngularVelocity(Vector3(0, 0, 0));
	cam->setPos(player->getPos().p + Vector3(0, 0, -10));
	cam->lookAt(player->getRigidBody()->getGlobalPose());
}
