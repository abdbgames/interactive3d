// Welcome to the Rice Fields:
#ifndef platformInclude_h
#define platformInclude_h
#if _WIN32
#include <Windows.h>
#else
#include <math.h>
#include <string.h>

namespace kg
{
	inline char* strcpy_s(char *in, const size_t &len, const char *cp)
	{
		return strcpy(in, cp);
	}
}

#endif /* _WIN32 */
#include <cstdlib>
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else /* __APPLE__ */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif /* __APPLE__ */
#define TITLE "s3477450 Interactive 3D Assignment 3"

namespace kg
{
	void initGL(int *argc, char **argv);
}

#endif /* platformInclude_h */
