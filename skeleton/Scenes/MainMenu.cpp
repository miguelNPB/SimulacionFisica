#include "MainMenu.h"
#include "../SceneManager.h"
#include "Level1.h"

MainMenu::MainMenu(SceneManager* sceneManager, PxScene* gScene, PxPhysics* gPhysics, Camera* cam)
	: Scene(), sceneManager(sceneManager), gScene(gScene), gPhysics(gPhysics), cam(cam) {

	
}

void MainMenu::Update(float t) {
	Snippets::drawText("Proyecto final Miguel Perez", 70, 300, 0.2, 0.2, { 0.0, 1.0, 0.3 });
	
	Snippets::drawText("pulsa cualquier tecla para jugar", 110, 200, 0.12, 0.12, {0.0, 1.0, 0.3});
}

void MainMenu::initScene() {
}

void MainMenu::keyPress(unsigned char key) {
	goToLevel();
}

void MainMenu::goToLevel() {
	sceneManager->switchScene(new Level1(sceneManager, gScene, gPhysics, cam));
}