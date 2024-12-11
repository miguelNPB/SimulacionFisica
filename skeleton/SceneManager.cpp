#include "SceneManager.h"

SceneManager::SceneManager() {
	
}

SceneManager::~SceneManager() {

}

void SceneManager::initSceneManager(Scene* startScene) {
	currentScene = startScene;
}

void SceneManager::switchScene(Scene* newScene) {
	queuedScene = newScene;
	changeSceneFlag = true;
}

void SceneManager::Update(float t) {
	if (changeSceneFlag) {
		delete currentScene;

		currentScene = queuedScene;
		queuedScene = nullptr;

		currentScene->initScene();

		changeSceneFlag = false;
	}
	else
		currentScene->Update(t);
}

void SceneManager::keyPress(unsigned char key) {
	currentScene->keyPress(key);
}

void SceneManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	currentScene->onCollision(actor1, actor2);
}