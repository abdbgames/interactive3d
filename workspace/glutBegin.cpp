#include "stdafx.h"
#include "glutBegin.h"
#include "platformInclude.h"

Tute *tute = NULL;

void draw() { tute->draw(); }
void update() { tute->update(); }

void init(int *argc, char **argv, Tute *thisTute)
{
	tute = thisTute;

	if (!tute)
	{
		printf("No tute pointer given!\n");
		exit(EXIT_FAILURE);
	}

	tute->init();

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutCreateWindow(tute->getName());

	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glutKeyboardFunc(kg::keyboardControl::keyboardCallback);
	glutKeyboardUpFunc(kg::keyboardControl::keyboardUpCallback);
	glutDisplayFunc(draw);
	glutIdleFunc(update);

	glutMainLoop();

	tute->end();
}