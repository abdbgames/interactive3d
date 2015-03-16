#include "stdafx.h"
#include <math.h>
#include "vectors.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(const float &_x, const float &_y) : x(_x), y(_y), z(0.0f) {}
Vector3::Vector3(const float &_x, const float &_y, const float &_z) : x(_x), y(_y), z(_z) {}

void Vector3::normalise()
{
	float m = getMagnitude();
	x = x / m;
	y = y / m;
	z = z / m;
}

float Vector3::getMagnitude()
{
	return sqrtf((x*x) + (y*y) + (z*z));
}

float Vector3::getDistance(const Vector3 &a, const Vector3 &b)
{
	/*Vector3 t;

	t.x = b.x - a.x;
	t.y = b.y - b.x;
	t.z = b.z - a.z;*/

	return 0;//t.getMagnitude();
}

float Vector3::getDistanceTo(const Vector3 &b)
{
	return Vector3::getDistance(*this, b);
}