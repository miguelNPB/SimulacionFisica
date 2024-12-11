#pragma once
#include "Scenes/Scene.h"

class SceneManager
{
public:
	SceneManager();

	~SceneManager();

	void initSceneManager(Scene* startScene);

	void switchScene(Scene* newScene);

	void Update(float t);

	void keyPress(unsigned char key);

	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
private:
	Scene* currentScene = nullptr;
	Scene* queuedScene = nullptr;
	bool changeSceneFlag = false;
};

