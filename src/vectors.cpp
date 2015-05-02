#include <math.h>
#include "vectors.h"
#include "platformInclude.h"

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(const Vector3 &v) : x(v.x), y(v.y) {
	/* WARNING: This will ignore the z value! */ }
Vector2::Vector2(const float &_x, const float &_y) : x(_x), y(_y) {}
Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(const Vector2 &v) : x(v.x), y(v.y), z(0.0f) {}
Vector3::Vector3(const Vector2 &v, const float &_z) : x(v.x), y(v.y), z(_z) {}
Vector3::Vector3(const float &_x, const float &_y) : x(_x), y(_y), z(0.0f) {}
Vector3::Vector3(const float &_x, const float &_y, const float &_z) :
	x(_x), y(_y), z(_z) {}

void Vector2::normalise()
{
	float m = getMagnitude();
	x = x / m;
	y = y / m;
}

void Vector2::glPoint()
{
	glVertex3f(x, y, 0.0f);
}

float Vector2::getMagnitude()
{
	return sqrtf((x*x) + (y*y));
}

float Vector2::getDistance(const Vector2 &a, const Vector2 &b)
{
	Vector2 t;

	t.x = b.x - a.x;
	t.y = b.y - b.x;

	return t.getMagnitude();
}

float Vector2::getDistanceTo(const Vector2 &b)
{
	return Vector2::getDistance(*this, b);
}

void Vector3::normalise()
{
	float m = getMagnitude();
	x = x / m;
	y = y / m;
	z = z / m;
}

void Vector3::glPoint()
{
	glVertex3f(x, y, z);
}

float Vector3::getMagnitude()
{
	return sqrtf((x*x) + (y*y) + (z*z));
}

float Vector3::getDistance(const Vector3 &a, const Vector3 &b)
{
	Vector3 t;

	t.x = b.x - a.x;
	t.y = b.y - b.x;
	t.z = b.z - a.z;

	return t.getMagnitude();
}

float Vector3::getDistanceTo(const Vector3 &b)
{
	return Vector3::getDistance(*this, b);
}

// Operator overloading:
Vector2 operator +(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator -(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator *(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 operator /(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x / b.x, a.y / b.y);
}

Vector3 operator +(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator -(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 operator *(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 operator /(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vector2 operator +(const float &a, const Vector2 &b)
{
	return Vector2(a + b.x, a + b.y);
}

Vector2 operator -(const float &a, const Vector2 &b)
{
	return Vector2(a - b.x, a - b.y);
}

Vector2 operator *(const float &a, const Vector2 &b)
{
	return Vector2(a * b.x, a * b.y);
}

Vector2 operator /(const float &a, const Vector2 &b)
{
	return Vector2(a / b.x, a / b.y);
}

Vector3 operator +(const float &a, const Vector3 &b)
{
	return Vector3(a + b.x, a + b.y, a + b.z);
}

Vector3 operator -(const float &a, const Vector3 &b)
{
	return Vector3(a - b.x, a - b.y, a - b.z);
}

Vector3 operator *(const float &a, const Vector3 &b)
{
	return Vector3(a * b.x, a * b.y, a * b.z);
}

Vector3 operator /(const float &a, const Vector3 &b)
{
	return Vector3(a / b.x, a / b.y, a / b.z);
}

Vector2 operator +(const Vector2 &a, const float &b)
{
	return Vector2(a.x + b, a.y + b);
}

Vector2 operator -(const Vector2 &a, const float &b)
{
	return Vector2(a.x - b, a.y - b);
}

Vector2 operator *(const Vector2 &a, const float &b)
{
	return Vector2(a.x * b, a.y * b);
}

Vector2 operator /(const Vector2 &a, const float &b)
{
	return Vector2(a.x / b, a.y / b);
}

Vector3 operator +(const Vector3 &a, const float &b)
{
	return Vector3(a.x + b, a.y + b, a.z + b);
}

Vector3 operator -(const Vector3 &a, const float &b)
{
	return Vector3(a.x - b, a.y - b, a.z - b);
}

Vector3 operator *(const Vector3 &a, const float &b)
{
	return Vector3(a.x * b, a.y * b, a.z * b);
}

Vector3 operator /(const Vector3 &a, const float &b)
{
	return Vector3(a.x / b, a.y / b, a.z / b);
}

