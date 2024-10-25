#pragma once

class Vector3
{
public:
	float x, y, z;

	Vector3(float x = 0, float y = 0, float z = 0) :
		x(x), y(y), z(z) {};

	float magnitude();
	Vector3 normalize();
	float productScalar(const Vector3& other);
	Vector3 productVectorial(const Vector3& other);

	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	// multiplicar por escalar
	Vector3 operator*(float k);
	// multiplicar con otro vector
	Vector3 operator*(const Vector3& other);
};