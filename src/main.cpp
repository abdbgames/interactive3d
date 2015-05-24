#define TITLE "s3477450 Interactive 3D Assignment 3"

#include "Engine.h"
#include "PlatformInclude.h"
#include "Keyboard.h"
#include "Mouse.h"

int main(int argc, char **argv)
{
	// Set up default environment args:
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(kg::Engine::getWidth(), kg::Engine::getHeight());
	glutCreateWindow(TITLE);

	// By default use orthographic camera:
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

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

	glEnable(GL_NORMALIZE);

	unsigned scene = kg::Engine::pushScene(new kg::Scene(), true);

	glutMainLoop();

	return EXIT_SUCCESS;
}
