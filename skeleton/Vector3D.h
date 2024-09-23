#pragma once

class Vector3D
{
public:
	float x, y, z;

	Vector3D(float x = 0, float y = 0, float z = 0) :
		x(x), y(y), z(z) {};

	float magnitude();
	Vector3D normalize();
	Vector3D productScalar(const Vector3D& other);

	Vector3D operator+(const Vector3D& other);
	Vector3D operator-(const Vector3D& other);
	// multiplicar por escalar
	Vector3D operator*(float k);
	// multiplicar con otro vector
	Vector3D operator*(const Vector3D& other);
};