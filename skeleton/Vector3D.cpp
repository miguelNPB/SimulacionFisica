#include "Vector3D.h"
#include <cmath>

float Vector3::magnitude()
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize()
{
    float mod = magnitude();

    return Vector3(x / mod, y / mod, z / mod);
}

Vector3 Vector3::productScalar(const Vector3& other)
{
    return (x * other.x + y * other.y + z * other.z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return Vector3(this->x, this->y, this->z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return Vector3(this->x, this->y, this->z);
}

Vector3 Vector3::operator*(float k)
{
    return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator*(const Vector3& other)
{
    return productScalar(other);
}