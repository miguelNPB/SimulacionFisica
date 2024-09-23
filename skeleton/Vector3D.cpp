#include "Vector3D.h"
#include <cmath>

float Vector3D::magnitude()
{
    return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize()
{
    float mod = magnitude();

    return Vector3D(x / mod, y / mod, z / mod);
}

Vector3D Vector3D::productScalar(const Vector3D& other)
{
    return (x * other.x + y * other.y + z * other.z);
}

Vector3D Vector3D::operator+(const Vector3D& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return Vector3D(this->x, this->y, this->z);
}

Vector3D Vector3D::operator-(const Vector3D& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return Vector3D(this->x, this->y, this->z);
}

Vector3D Vector3D::operator*(float k)
{
    return Vector3D(x * k, y * k, z * k);
}

Vector3D Vector3D::operator*(const Vector3D& other)
{
    return productScalar(other);
}