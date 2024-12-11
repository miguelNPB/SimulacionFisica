#pragma once
#include "Scene.h"
#include "../Render/Render.h"

class SceneManager;
class MainMenu;

class YouWin : public Scene
{
public:
	YouWin(SceneManager* sceneManager, PxScene* gScene, PxPhysics* gPhysics, Camera* cam);

	virtual void Update(float t);

	virtual void initScene();

	virtual void keyPress(unsigned char key);
private:
	void goToMainMenu();

	SceneManager* sceneManager;
	PxScene* gScene;
	PxPhysics* gPhysics;
	Camera* cam;
};

