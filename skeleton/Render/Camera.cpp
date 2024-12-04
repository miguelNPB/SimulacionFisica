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
		case 'W':	mOrbitRadius -= speed;		break; // Acercar c�mara
		case 'S':	mOrbitRadius += speed;		break; // Alejar c�mara
		case 'A':	// Rotaci�n horizontal extra con teclas (opcional)
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

		// Obtener la posici�n del objeto a seguir
		PxVec3 lookingAt = lookingAtTransform.p;

		// Vector desde la c�mara hacia el punto de inter�s
		PxVec3 cameraToTarget = mEye - lookingAt;

		// Normalizar el vector para trabajar con direcciones
		cameraToTarget.normalize();

		// Sensibilidad de rotaci�n (ajustar seg�n necesidad)
		float rotationSpeed = 0.005f;

		// Rotaciones en radianes
		float yaw = dx * rotationSpeed;   // Rotaci�n horizontal (alrededor del eje Y)
		float pitch = dy * rotationSpeed; // Rotaci�n vertical (alrededor del eje X)

		// Rotar alrededor del eje Y (yaw)
		PxQuat yawRotation(yaw, PxVec3(0, 1, 0));
		cameraToTarget = yawRotation.rotate(cameraToTarget);

		// Crear un eje perpendicular para la rotaci�n en pitch
		PxVec3 pitchAxis = cameraToTarget.cross(PxVec3(0, 1, 0)).getNormalized();
		PxQuat pitchRotation(pitch, pitchAxis);
		cameraToTarget = pitchRotation.rotate(cameraToTarget);

		// Actualizar la posici�n de la c�mara basada en el nuevo vector y radio
		mEye = lookingAt + cameraToTarget * FOV;

		// Actualizar la direcci�n de la c�mara para que apunte al objeto
		mDir = (lookingAt - mEye).getNormalized();

		// Actualizar las coordenadas del rat�n
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
		// Actualizar el transform del objeto que la c�mara sigue
		lookingAtTransform = tr;

		// Calcular la nueva posici�n de la c�mara bas�ndonos en el radio y el vector de direcci�n actual
		PxVec3 lookingAt = tr.p; // Posici�n del objeto
		PxVec3 cameraToTarget = mEye - lookingAt; // Direcci�n actual desde la c�mara al objeto

		// Asegurar que el vector est� normalizado para calcular la posici�n de la c�mara
		if (cameraToTarget.magnitude() == 0) {
			// Si la c�mara ya est� en el centro del objeto, la movemos a una posici�n inicial
			cameraToTarget = PxVec3(0, 0, -1); // Mirando hacia adelante por defecto
		}
		cameraToTarget.normalize();

		// Actualizar la posici�n de la c�mara para mantener el radio de �rbita
		mEye = lookingAt + cameraToTarget * FOV;

		mEye.y = INCLINATION;

		// Actualizar la direcci�n de la c�mara para que siga mirando al objeto
		mDir = (lookingAt - mEye).getNormalized();
	}

	void Camera::lookAt(const physx::PxTransform& tr) {
		// Ajustar la direcci�n hacia un objetivo espec�fico
		mDir = tr.p - mEye;
	}

}