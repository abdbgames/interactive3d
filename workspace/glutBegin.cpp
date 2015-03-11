#include "stdafx.h"
#include "glutBegin.h"
#include "platformInclude.h"

Tute *tute = NULL;

void init(int *argc, char **argv, Tute *thisTute)
{
	tute = thisTute;

	if (!tute)
	{
		printf("No tute pointer given!\n");
		exit(EXIT_FAILURE);
	}

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(tute->getName());

	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glutKeyboardFunc(kg::keyboardControl::keyboardCallback);
	glutDisplayFunc( [](){tute->draw();} );
	glutIdleFunc( [](){tute->update();} );

	glutMainLoop();
}