#ifndef misc_h
#define misc_h

#include "PlatformInclude.h"
#include "Vectors.h"

namespace kg
{
	template <typename T>
	void clamp(T &in, const T &min, const T &max);
	template <typename T>
	void range(T &in, const T &min, const T &max);

	template <typename T>
	T getRandom(const T &min, const T &max);

	void drawAxis(const Vector3 &pos, const float &size);
	void drawAxis(const float &size);
	void drawNormal(Vector3 &from, Vector3 &to);

	GLuint loadTexture(const char *filename);
}

#endif /* misc_h */
