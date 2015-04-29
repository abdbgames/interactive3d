#include "stdafx.h"
#include "glutBegin.h"
#include "platformInclude.h"
#include "ass2.h"

Tute *tute = NULL;

// Default screen width and height values:
const int screenWidth = 1024,
	screenHeight = 768;

void draw() { tute->draw(); }
void update() { tute->update(); }

void init(int *argc, char **argv, Tute *thisTute)
{
	/* Inital stuff for setting up a GL/glut context
	 * also sets up the callbacks for our draw/update etc
	 * and starts the main loop. */

	tute = thisTute;

	if (!tute)
	{
		printf("No tute pointer given!\n");
		exit(EXIT_FAILURE);
	}

	tute->init();
	
	Ass2::grabSize(screenWidth, screenHeight);

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow(tute->getName());

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
	glutDisplayFunc(draw);
	glutIdleFunc(update);
	glutReshapeFunc(Ass2::grabSize);

	glutMainLoop();

	tute->end();
}

