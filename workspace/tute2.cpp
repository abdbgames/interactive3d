#include "stdafx.h"
#include "tute2.h"
#include "keyboard.h"
#include <math.h>

void Tute2::init()
{
	m_steps = 300;
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

	if (kg::keyboardControl::onKeyPressed(KGkey_s))
		m_pos.y -= 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_w))
		m_pos.y += 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_a))
		m_pos.x -= 0.01f;

	if (kg::keyboardControl::onKeyPressed(KGkey_d))
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
	drawFormula(-1, 1);
	//drawCircleCartesian();
	//drawCirecleParametric();
	drawTangent(0.8);

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

void Tute2::drawCircleCartesian()
{
	float x = -m_r;
	float xS = 2 * m_r / m_steps;
	float y = m_pos.y;

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= m_steps; ++i)
	{
		y = m_pos.y + sqrtf(m_r * m_r - x * x);
		glVertex3f(m_pos.x + x, y, 0.1);
		x += xS;
	}
	for (int i = 0; i <= m_steps; ++i)
	{
		y = m_pos.y - sqrtf(m_r * m_r - x * x);
		glVertex3f(m_pos.x + x, y, 0.1);
		x -= xS;
	}
	glEnd();
}

void Tute2::drawCirecleParametric()
{
	float x, y, t;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= m_steps; ++i)
	{
		t = (i / (float)m_steps) * 2 * KG_PI;
		x = m_r * cosf(t);
		y = m_r * sinf(t);
		glVertex3f(m_pos.x + x, m_pos.y + y, m_pos.z);
	}
	glEnd();
}

void Tute2::drawFormula(const float &xMin, const float &xMax)
{
	glColor3f(1.0, 1.0, 1.0);

	float xDist = (xMax - xMin) / m_steps;
	float x = xMin;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= m_steps; ++i)
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
	Vector3 start(x, x * x);
	drawLine(start, start + Vector3(1, 2 * x), true);
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

void Tute2::drawLine(Vector3 &pos, const Vector3 &to, const bool &normalise)
{
	glColor3f(1.0, 1.0, 0.0);

	Vector3 d;

	if (normalise)
	{
		d = to;
		d.normalise();
	}
	else
		d = to;

	glBegin(GL_LINE_STRIP);
	pos.glPoint();
	d.glPoint();
	glEnd();
}
