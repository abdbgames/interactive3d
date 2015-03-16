#include "stdafx.h"
#include "tute2.h"
#include "keyboard.h"

void Tute2::init()
{

}

void Tute2::update()
{
	kg::keyboardControl::keyBufferBegin();
	kg::keyboardControl::keyBufferEnd();
}

void Tute2::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	drawAxis(0, 0, 0, 1);
	drawFormula(-1, 1, 1000);

	glutSwapBuffers();
}

void Tute2::end()
{

}

void Tute2::drawAxis(float x, float y, float z, float size)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(x + size, y, z);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(x, y + size, z);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + size);
	glEnd();
}

void Tute2::drawFormula(float xMin, float xMax, int steps)
{
	glColor3f(1.0, 1.0, 1.0);

	float xDist = (xMax - xMin) / steps;
	float x = xMin;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= steps; ++i)
	{
		x += xDist * i;
		//float y = getLinearY(x);
		float y = getQuadraticY(x);

		glVertex3f(x, y, 0.1);
	}
	glEnd();
}

void Tute2::drawTangent(float x)
{

}

float Tute2::getLinearY(float x)
{
	//return x;
	//return 2 * x + 1;
	return -(2 * x);
}

float Tute2::getQuadraticY(float x)
{
	return x * x;
	//return 2 * x * x - 1;
	//return -(2 * x * x) + (2 * x) + 1;
}