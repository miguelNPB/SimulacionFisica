#include "YouWin.h"
#include "../SceneManager.h"
#include "MainMenu.h"

YouWin::YouWin(SceneManager* sceneManager, PxScene* gScene, PxPhysics* gPhysics, Camera* cam)
	: Scene(), sceneManager(sceneManager), gScene(gScene), gPhysics(gPhysics), cam(cam) {

	cam->setPos(Vector3(0,0,0));
	cam->lookAt(PxTransform(Vector3(0, 0, 0)));
}

void YouWin::Update(float t) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Snippets::drawText("Has ganado!", 150, 300, 0.2, 0.2, { 0.0, 1.0, 0.3 });

	Snippets::drawText("pulsa cualquier tecla para avanzar", 110, 200, 0.12, 0.12, { 0.0, 1.0, 0.3 });
}

void YouWin::initScene() {

}

void YouWin::keyPress(unsigned char key) {
	goToMainMenu();
}

void YouWin::goToMainMenu() {
	sceneManager->switchScene(new MainMenu(sceneManager, gScene, gPhysics, cam));
}