#include <math.h>

#include "vectors.h"

namespace kg
{
	Vector2::Vector2() : x(0.0f), y(0.0f) {}
	Vector2::Vector2(const Vector3 &v) : x(v.x), y(v.y) {
		/* WARNING: This will ignore the z value! */
	}
	Vector2::Vector2(const float &_x, const float &_y) : x(_x), y(_y) {}
	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3::Vector3(const Vector2 &v) : x(v.x), y(v.y), z(0.0f) {}
	Vector3::Vector3(const Vector2 &v, const float &_z) : x(v.x), y(v.y),
		z(_z) {}
	Vector3::Vector3(const float &_x, const float &_y) : x(_x), y(_y),
		z(0.0f) {}
	Vector3::Vector3(const float &_x, const float &_y, const float &_z)
		: x(_x), y(_y), z(_z) {}

	void Vector2::normalise()
	{
		float m = getMagnitude();
		x = x / m;
		y = y / m;
	}

	float Vector2::getMagnitude()
	{
		return sqrtf((x * x) + (y * y));
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

	float Vector2::getDotProduct(const Vector2 &a, const Vector2 &b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	void Vector3::normalise()
	{
		float m = getMagnitude();
		x = x / m;
		y = y / m;
		z = z / m;
	}

	float Vector3::getMagnitude()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
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
		return getDistance(*this, b);
	}

	float Vector3::getDotProduct(const Vector3 &a, const Vector3 &b)
	{
		return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
	}

	Vector3 Vector3::getCrossProduct(const Vector3 &a, const Vector3 &b)
	{
		Vector3 ret;

		ret.x = a.y * b.z - b.y * a.z;
		ret.y = a.x * b.z - b.x * a.z;
		ret.z = a.x * b.y - b.x * a.y;

		return ret;
	}
}

// Operator overloading:
kg::Vector2 operator +(const kg::Vector2 &a, const kg::Vector2 &b)
{
	return kg::Vector2(a.x + b.x, a.y + b.y);
}

kg::Vector2 operator -(const kg::Vector2 &a, const kg::Vector2 &b)
{
	return kg::Vector2(a.x - b.x, a.y - b.y);
}

kg::Vector2 operator *(const kg::Vector2 &a, const kg::Vector2 &b)
{
	return kg::Vector2(a.x * b.x, a.y * b.y);
}

kg::Vector2 operator /(const kg::Vector2 &a, const kg::Vector2 &b)
{
	return kg::Vector2(a.x / b.x, a.y / b.y);
}

kg::Vector3 operator +(const kg::Vector3 &a, const kg::Vector3 &b)
{
	return kg::Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

kg::Vector3 operator -(const kg::Vector3 &a, const kg::Vector3 &b)
{
	return kg::Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

kg::Vector3 operator *(const kg::Vector3 &a, const kg::Vector3 &b)
{
	return kg::Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

kg::Vector3 operator /(const kg::Vector3 &a, const kg::Vector3 &b)
{
	return kg::Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

kg::Vector2 operator +(const float &a, const kg::Vector2 &b)
{
	return kg::Vector2(a + b.x, a + b.y);
}

kg::Vector2 operator -(const float &a, const kg::Vector2 &b)
{
	return kg::Vector2(a - b.x, a - b.y);
}

kg::Vector2 operator *(const float &a, const kg::Vector2 &b)
{
	return kg::Vector2(a * b.x, a * b.y);
}

kg::Vector2 operator /(const float &a, const kg::Vector2 &b)
{
	return kg::Vector2(a / b.x, a / b.y);
}

kg::Vector3 operator +(const float &a, const kg::Vector3 &b)
{
	return kg::Vector3(a + b.x, a + b.y, a + b.z);
}

kg::Vector3 operator -(const float &a, const kg::Vector3 &b)
{
	return kg::Vector3(a - b.x, a - b.y, a - b.z);
}

kg::Vector3 operator *(const float &a, const kg::Vector3 &b)
{
	return kg::Vector3(a * b.x, a * b.y, a * b.z);
}

kg::Vector3 operator /(const float &a, const kg::Vector3 &b)
{
	return kg::Vector3(a / b.x, a / b.y, a / b.z);
}

kg::Vector2 operator +(const kg::Vector2 &a, const float &b)
{
	return kg::Vector2(a.x + b, a.y + b);
}

kg::Vector2 operator -(const kg::Vector2 &a, const float &b)
{
	return kg::Vector2(a.x - b, a.y - b);
}

kg::Vector2 operator *(const kg::Vector2 &a, const float &b)
{
	return kg::Vector2(a.x * b, a.y * b);
}

kg::Vector2 operator /(const kg::Vector2 &a, const float &b)
{
	return kg::Vector2(a.x / b, a.y / b);
}

kg::Vector3 operator +(const kg::Vector3 &a, const float &b)
{
	return kg::Vector3(a.x + b, a.y + b, a.z + b);
}

kg::Vector3 operator -(const kg::Vector3 &a, const float &b)
{
	return kg::Vector3(a.x - b, a.y - b, a.z - b);
}

kg::Vector3 operator *(const kg::Vector3 &a, const float &b)
{
	return kg::Vector3(a.x * b, a.y * b, a.z * b);
}

kg::Vector3 operator /(const kg::Vector3 &a, const float &b)
{
	return kg::Vector3(a.x / b, a.y / b, a.z / b);
}

