#include "Camera.h"
#include <ctype.h>
#include "foundation/PxMat33.h"
#include <iostream>
#include <glut.h>

using namespace physx;

namespace Snippets
{

	Camera::Camera(const PxVec3& eye, const PxVec3& dir)
	{
		mEye = eye;
		mDir = dir.getNormalized();
		mMouseX = 0;
		mMouseY = 0;
		FOV = 15.0f; // Radio por defecto
		lookingAtTransform = PxTransform(PxVec3(0, 0, 0)); // Inicializar a un origen por defecto
	}

	void Camera::handleMouse(int button, int state, int x, int y)
	{
		PX_UNUSED(state);
		PX_UNUSED(button);
		mMouseX = x;
		mMouseY = y;

		if (state == 1 && (button == 0 || button == 1))
			glutWarpPointer(500, 500);
		//std::cout << state << " " << button << "\n";
	}

	bool Camera::handleKey(unsigned char key, int x, int y, float speed)
	{
		PX_UNUSED(x);
		PX_UNUSED(y);

		/*PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		switch (toupper(key))
		{
		case 'W':	mOrbitRadius -= speed;		break; // Acercar cámara
		case 'S':	mOrbitRadius += speed;		break; // Alejar cámara
		case 'A':	// Rotación horizontal extra con teclas (opcional)
		case 'D':	break;
		default:	return false;
		}*/
		return true;
	}

	void Camera::handleAnalogMove(float x, float y)
	{
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		mEye += mDir * y;
		mEye += viewY * x;
	}

	void Camera::handleMotion(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		// Obtener la posición del objeto a seguir
		PxVec3 lookingAt = lookingAtTransform.p;

		// Vector desde la cámara hacia el punto de interés
		PxVec3 cameraToTarget = mEye - lookingAt;

		// Normalizar el vector para trabajar con direcciones
		cameraToTarget.normalize();

		// Sensibilidad de rotación (ajustar según necesidad)
		float rotationSpeed = 0.005f;

		// Rotaciones en radianes
		float yaw = dx * rotationSpeed;   // Rotación horizontal (alrededor del eje Y)
		float pitch = dy * rotationSpeed; // Rotación vertical (alrededor del eje X)

		// Rotar alrededor del eje Y (yaw)
		PxQuat yawRotation(yaw, PxVec3(0, 1, 0));
		cameraToTarget = yawRotation.rotate(cameraToTarget);

		// Crear un eje perpendicular para la rotación en pitch
		PxVec3 pitchAxis = cameraToTarget.cross(PxVec3(0, 1, 0)).getNormalized();
		PxQuat pitchRotation(pitch, pitchAxis);
		cameraToTarget = pitchRotation.rotate(cameraToTarget);

		// Actualizar la posición de la cámara basada en el nuevo vector y radio
		mEye = lookingAt + cameraToTarget * FOV;

		// Actualizar la dirección de la cámara para que apunte al objeto
		mDir = (lookingAt - mEye).getNormalized();

		// Actualizar las coordenadas del ratón
		mMouseX = x;
		mMouseY = y;
	}

	PxTransform Camera::getTransform() const
	{
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0));

		if (viewY.normalize() < 1e-6f)
			return PxTransform(mEye);

		PxMat33 m(mDir.cross(viewY), viewY, -mDir);
		return PxTransform(mEye, PxQuat(m));
	}

	PxVec3 Camera::getEye() const
	{
		return mEye;
	}

	PxVec3 Camera::getDir() const
	{
		return mDir;
	}

	void Camera::setPos(const physx::PxVec3& newPos) {
		mEye = newPos;
	}

	void Camera::updateFollow(const physx::PxTransform& tr) {
		// Actualizar el transform del objeto que la cámara sigue
		lookingAtTransform = tr;

		// Calcular la nueva posición de la cámara basándonos en el radio y el vector de dirección actual
		PxVec3 lookingAt = tr.p; // Posición del objeto
		PxVec3 cameraToTarget = mEye - lookingAt; // Dirección actual desde la cámara al objeto

		// Asegurar que el vector esté normalizado para calcular la posición de la cámara
		if (cameraToTarget.magnitude() == 0) {
			// Si la cámara ya está en el centro del objeto, la movemos a una posición inicial
			cameraToTarget = PxVec3(0, 0, -1); // Mirando hacia adelante por defecto
		}
		cameraToTarget.normalize();

		// Actualizar la posición de la cámara para mantener el radio de órbita
		mEye = lookingAt + cameraToTarget * FOV;

		mEye.y = INCLINATION;

		// Actualizar la dirección de la cámara para que siga mirando al objeto
		mDir = (lookingAt - mEye).getNormalized();
	}

	void Camera::lookAt(const physx::PxTransform& tr) {
		// Ajustar la dirección hacia un objetivo específico
		mDir = tr.p - mEye;
	}

}