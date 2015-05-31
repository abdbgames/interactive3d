#ifndef misc_h
#define misc_h

#include <sstream>
#include <string>

#include "platformInclude.h"
#include "vectors.h"

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

	float lerpf(const float &from, const float &to, const float &delta);
	float degToRad(const float &in);
	float radToDeg(const float &in);

	void keepDegRange(float &in);
	void keepRadRange(float &in);
	void drawAxis(const Vector3 &pos, const float &size);
	void drawAxis(const float &size);
	void drawNormal(Vector3 &from, Vector3 &to);

	GLuint loadTexture(const char *filename);
}

// std::string concatenation with different types:
template <typename T>
std::string kgcc(const T &l, const std::string &r, const bool &flip)
{
	std::stringstream ss;
	if (flip)
		ss << r << l;
	else
		ss << l << r;
	return ss.str();
}

std::string operator +(const std::string &l, const float &r);
std::string operator +(const float &l, const std::string &r);
std::string operator +(const std::string &l, const int &r);
std::string operator +(const int &l, const std::string &r);
std::string operator +(const std::string &l, const unsigned &r);
std::string operator +(const unsigned &l, const std::string &r);
std::string operator +(const std::string &l, const bool &r);
std::string operator +(const bool &l, const std::string &r);

#endif /* misc_h */
