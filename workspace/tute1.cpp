#include "stdafx.h"
#include "tute1.h"
#include "keyboard.h"

void Tute1::init()
{

}

void Tute1::update()
{
	kg::keyboardControl::keyBufferBegin();
	kg::keyboardControl::keyBufferEnd();
}

void Tute1::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, -0.75);
	glVertex3f(0.75, -0.25, -0.75);
	glVertex3f(0.75, 0.75, -0.75);
	glVertex3f(-0.25, 0.75, -0.75);
	glEnd();

	//printf("%s\n", gluErrorString(glGetError()));

	glutSwapBuffers();
}

void Tute1::end()
{

}
