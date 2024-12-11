#pragma once
#include "Scene.h"
#include "../Render/Render.h"

class SceneManager;
class Level1;

class MainMenu : public Scene
{
public:
	MainMenu(SceneManager* sceneManager, PxScene* gScene, PxPhysics* gPhysics, Camera* cam);

	virtual void Update(float t);

	virtual void initScene();

	virtual void keyPress(unsigned char key);
private:
	void goToLevel();

	SceneManager* sceneManager;
	PxScene* gScene;
	PxPhysics* gPhysics;
	Camera* cam;
};

