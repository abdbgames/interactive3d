#include "stdafx.h"
#include "tute2.h"
#include "keyboard.h"
#include <math.h>

void Tute2::init()
{
	m_steps = 100;
	m_r = 0.3f;
	m_pos = Vector3(0, 0, 0);
}

void Tute2::update()
{
	kg::keyboardControl::keyBufferBegin();

	if (kg::keyboardControl::onKeyPressed(KGkey_p))
		++m_steps;

	if (kg::keyboardControl::onKeyPressed(KGkey_o))
		--m_steps;

	if (kg::keyboardControl::onKeyPressed(KGkey_j))
		m_r -= 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_k))
		m_r += 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_down))
		m_pos.y -= 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_up))
		m_pos.y += 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_left))
		m_pos.x -= 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_right))
		m_pos.x += 0.01f;

	glFlush();

	kg::keyboardControl::keyBufferEnd();

	glutPostRedisplay();
}

void Tute2::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	drawAxis(0, 0, 0, 1);
	//drawFormula(-1, 1, m_steps);
	drawCircleCartesian(m_pos, m_r, m_steps);

	glutSwapBuffers();
}

void Tute2::end()
{

}

void Tute2::drawAxis(const float &x, const float &y, const float &z, const float &size)
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

void Tute2::drawCircleCartesian(const Vector3 &v, const float &r, const int &steps)
{
	float x = v.x - r;
	float xS = 2 * r / steps;
	float y = v.y;

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= steps; ++i)
	{
		y = sqrtf(r * r - x * x);
		glVertex3f(x, y, 0.1);
		x += xS;
	}
	for (int i = 0; i <= steps; ++i)
	{
		y = -sqrtf(r * r - x * x);
		glVertex3f(x, y, 0.1);
		x -= xS;
	}
	glEnd();
}

void Tute2::drawFormula(const float &xMin, const float &xMax, const int &steps)
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

void Tute2::drawTangent(const float &x)
{

}

float Tute2::getLinearY(const float &x)
{
	//return x;
	//return 2 * x + 1;
	return -(2 * x);
}

float Tute2::getQuadraticY(const float &x)
{
	return x * x;
	//return 2 * x * x - 1;
	//return -(2 * x * x) + (2 * x) + 1;
}
