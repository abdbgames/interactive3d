#include "PlatformInclude.h"
#include "Engine.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace kg
{
	void initGL(int *argc, char **argv)
	{
		// Setup default environment args:
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(kg::Engine::getWidth(), kg::Engine::getHeight());
		glutCreateWindow(TITLE);

		// Setup initial environment args:
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glEnable(GL_CULL_FACE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		// Setup GL callbacks:
		glutSpecialFunc(kg::keyboardControl::specialCallback);
		glutSpecialUpFunc(kg::keyboardControl::specialUpCallback);
		glutKeyboardFunc(kg::keyboardControl::keyboardCallback);
		glutKeyboardUpFunc(kg::keyboardControl::keyboardUpCallback);
		glutPassiveMotionFunc(kg::mouseControl::mouseMoveCallback);
		glutMotionFunc(kg::mouseControl::mouseMoveCallback);
		glutMouseFunc(kg::mouseControl::mousePressCallback);
		glutDisplayFunc(kg::Engine::renderCallback);
		glutIdleFunc(kg::Engine::updateCallback);
		glutReshapeFunc(kg::Engine::resizeCallback);

		// By default use orthographic camera:
		glMatrixMode(GL_PROJECTION);
		glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
	}
}