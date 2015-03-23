#ifndef vectors_h
#define vectors_h

struct Vector3;

struct Vector2
{
	Vector2();
	Vector2(const Vector3 &v);
	Vector2(const float &_x, const float &_y);

	void normalise();
	void glPoints();

	float x, y;
	float getMagnitude();
	float getDistanceTo(const Vector2 &b);

	static float getDistance(const Vector2 &a, const Vector2 &b);
};

struct Vector3
{
	Vector3();
	Vector3(const Vector2 &v);
	Vector3(const Vector2 &v, const float &_z);
	Vector3(const float &_x, const float &_y);
	Vector3(const float &_x, const float &_y, const float &_z);

	void normalise();
	void glPoints();

	float x, y, z;
	float getMagnitude();
	float getDistanceTo(const Vector3 &b);

	static float getDistance(const Vector3 &a, const Vector3 &b);
};

Vector2 operator +(const Vector2 &a, const Vector2 &b);
Vector2 operator -(const Vector2 &a, const Vector2 &b);
Vector2 operator *(const Vector2 &a, const Vector2 &b);
Vector3 operator +(const Vector3 &a, const Vector3 &b);
Vector3 operator -(const Vector3 &a, const Vector3 &b);
Vector3 operator *(const Vector3 &a, const Vector3 &b);

#endif /* vectors_h */