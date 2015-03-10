#ifndef platformInclude_h
#define platformInclude_h
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
// allow us to easily pass function pointers:
typedef void(*VoidF)();
#if _WIN32
#   include <Windows.h>
#endif /* _WIN32 */
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else /* __APPLE__ */
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif /* __APPLE__ */
#endif /* platformInclude_h */