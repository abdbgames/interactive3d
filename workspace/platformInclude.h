#ifndef platformInclude_h
#define platformInclude_h
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
// For SOIL image loader: https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
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
// pi:
#define KG_PI 3.14159265359
#define KG_GR 9.8
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
#endif /* platformInclude_h */

