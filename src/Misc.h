#ifndef misc_h
#define misc_h

#include "PlatformInclude.h"
#include "Vectors.h"

namespace kg
{
	template <typename T>
	T kgmin(const T &a, const T &b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	T kgmax(const T &a, const T &b)
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	void kgabs(T &in)
	{
		return (in < 0) ? (in * -1) : in;
	}

	template <typename T>
	void clamp(T &in, const T &min, const T &max)
	{
		if (in > max)
			in = max;
		else if (in < min)
			in = min;
	}

	template <typename T>
	void range(T &in, const T &min, const T &max)
	{
		T range = max - min;
		while (in > max)
			in -= range;

		while (in < min)
			in += range;
	}

	template <typename T>
	T getRandom(const T &min, const T &max)
	{
		// Generates a random type in the range given:
		if (max < min)
			return 0.0f;

		float diff = max - min;

		return (diff == 0.0f) ? 0.0f :
			min + ((((T)(rand())) / (T)(RAND_MAX)) * diff);
	}

	void drawAxis(const Vector3 &pos, const float &size);
	void drawAxis(const float &size);
	void drawNormal(Vector3 &from, Vector3 &to);

	GLuint loadTexture(const char *filename);
}

#endif /* misc_h */
