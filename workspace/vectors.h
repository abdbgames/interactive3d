#ifndef vectors_h
#define vectors_h

struct Vector3
{
	Vector3();
	Vector3(const float &_x, const float &_y);
	Vector3(const float &_x, const float &_y, const float &_z);

	void normalise();

	float x, y, z;
	float getMagnitude();
	float getDistanceTo(const Vector3 &b);

	static float getDistance(const Vector3 &a, const Vector3 &b);
};

#endif /* vectors_h */