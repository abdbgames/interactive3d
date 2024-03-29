// Welcome to the Rice Fields:
#ifndef platformInclude_h
#define platformInclude_h
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>
// Program uses the Simple OpenGL Image Library for loading textures:
// http://www.lonesock.net/soil.html
#include <SOIL.h>
// A press type:
enum KG_PRESS_TYPE
{
	KG_DOWN,
	KG_UP,
	KG_PRESSED,
};
// A draw type mode:
enum KG_DRAW_MODE
{
	KG_FILLED,
	KG_FILLED_NOCULL,
	KG_WIRE,
	KG_POINTS,
};
// A Lighting mode:
enum KG_LIGHT_MODE
{
	KG_FULL,
	KG_DIR, // Directional only.
	KG_UNLIT,
};
// allow us to easily pass function pointers:
typedef void(*VoidF)();
// Pi:
#define KG_PI 3.14159265359
// Gravity:
#define KG_GR 9.8f
// min and max macro functions:
#define kgmin(X, Y) (((X) < (Y)) ? (X) : (Y))
#define kgmax(X, Y) (((X) > (Y)) ? (X) : (Y))
// Misc functions (misc.cpp):
struct Vector3;
namespace kg
{
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
}
// Constant milliseconds value to divide from seconds:
#define milli 1000
#if _WIN32
#  include <Windows.h>
#else /* _WIN32 */
#include <math.h>
// Visual Studio is a piece of shit:
#include <string.h>
#define _strdup strdup
#endif /* _WIN32 */
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else /* __APPLE__ */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif /* __APPLE__ */
// See misc.cpp ln 76:
GLuint loadTexture(const char *filename);
#endif /* platformInclude_h */
