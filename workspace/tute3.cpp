#include "stdafx.h"
#include "Tute3.h"
#include "keyboard.h"

bool debug = false;
bool showTangents = false;
bool showNormals = false;
bool go = false;
bool canGo = true;

struct state
{
	Vector2 r0, v0, r, v;
};

state projectile = {
	Vector2(0.0, 0.0),
	Vector2(1.0, 2.0),
	Vector2(0.0, 0.0),
	Vector2(1.0, 2.0)
};

const float g = -9.8;

float startTime;
float rot = 1.0f;
float speed = 1.0f;
const float incSpeed = 1.0f;
const int milli = 1000;

typedef enum { analytical, numerical } integrationMode;
integrationMode integrateMode = analytical;

bool cartesianMode = false;

void keyI()
{
	if (integrateMode == analytical)
		integrateMode = numerical;
	else
		integrateMode = analytical;
}

void keyS()
{
	if (!canGo) return;
	startTime = glutGet(GLUT_ELAPSED_TIME) / (float)milli;
	go = true;
	canGo = false;
}

void keyF()
{
	printf("Switching to %s mode...\n", (cartesianMode) ? "parametric" : "cartesian");
	cartesianMode = (cartesianMode) ? false : true;
}

void updateProjectileStateAnalytical(float t)
{
	projectile.r.x = projectile.v0.x * t + projectile.r0.x;
	projectile.r.y = 1.0 / 2.0 * g * t * t + projectile.v0.y * t + projectile.r0.y;
	/*
	* The above statement can alternatively be written as below, saving
	* a few arithmetic operations, which may or may not be worthwhile
	* and which can obscure code and introduce hard to find bugs:
	*
	* 1) Precalculate 1.0 / 2.0 as 0.5 to save a division
	* projectileState.r.y = 0.5 * g * t * t + v0.y * t + r0.y;
	*
	* 2) Factorise to save a multiplication
	* projectileState.r.y = t * (0.5 * g * t + v0.y) + r0.y;
	*/
}

void updateProjectileStateNumerical(float dt)
{
	// Euler integration

	// Position
	projectile.r.x += projectile.v.x * dt;
	projectile.r.y += projectile.v.y * dt;

	// Velocity
	projectile.v.y += g * dt;
}

void updateProjectileState(float t, float dt)
{
	if (debug)
		printf("integrateMode: %d\n", integrateMode);
	if (integrateMode == analytical)
		updateProjectileStateAnalytical(t);
	else
		updateProjectileStateNumerical(dt);
}


void Tute3::init()
{
	kg::keyboardControl::setKeyPress(KGkey_i, "I KEY", keyI);
	kg::keyboardControl::setKeyPress(KGkey_space, "S KEY", keyS);
	kg::keyboardControl::setKeyPress(KGkey_f, "F Key", keyF);
}

void Tute3::updateTime()
{
	static float lastT = -1.0;

	t = glutGet(GLUT_ELAPSED_TIME) / (float)milli - startTime;

	if (lastT < 0.0)
	{
		lastT = t;
		return;
	}

	dt = t - lastT;

	lastT = t;
}

void Tute3::update()
{
	kg::keyboardControl::keyBufferBegin();

	updateTime();

	if (debug)
		printf("%f %f\n", t, dt);

	if (go)
	{
		updateProjectileState(t, dt);
		
		if (projectile.r.y < 0.0f)
		{
			projectile.r.y = 0.0f;
			go = false;
			canGo = true;
			projectile.r0 = projectile.r;
		}
	}

	if (kg::keyboardControl::onKeyPress(KGkey_D))
	{
		// Shift+D to enable/disable debug:
		printf("Turning debug mode %s\n", (debug) ? "off" : "on");
		debug = (debug) ? false : true;
	}

	if (kg::keyboardControl::onKeyPressed(KGkey_a))
		rot += incSpeed * dt;

	if (kg::keyboardControl::onKeyPressed(KGkey_d))
		rot -= incSpeed * dt;

	if (kg::keyboardControl::onKeyPressed(KGkey_w))
		speed += incSpeed * dt;

	if (kg::keyboardControl::onKeyPressed(KGkey_s))
		speed -= incSpeed * dt;

	projectile.v0.x = cosf(rot) * speed;
	projectile.v0.y = sinf(rot) * speed;

	kg::keyboardControl::keyBufferEnd();

	glutPostRedisplay();
}

void displayProjectile(void)
{
	glColor3f(0.8, 0.8, 0.8);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(projectile.r.x, projectile.r.y);
	glEnd();
}

void drawParabola(const int &steps)
{
	glColor3f(0.0, 0.0, 1.0);

	float flightTime = (2.0 * speed * sinf(rot)) / -g, x, y,
		in = flightTime / (float)steps,
		preCalc = (1 / (float)2) * g;

	glBegin(GL_LINE_STRIP);
	glVertex3f(projectile.r.x, projectile.r.y, 0.0);
	for (int i = 1; i <= steps; ++i)
	{
		float t = i * in;
		x = projectile.v0.x * t + projectile.r.x;
		y = (preCalc * t * t) + (projectile.v0.y * t) + projectile.r.y;
		glVertex3f(x, y, 0.0);
	}
	glEnd();
}

void drawVelocity()
{
	glColor3f(1.0, 0.0, 1.0);

	Vector2 v(projectile.r.x + projectile.v0.x/5.5, projectile.r.y + projectile.v0.y/5.5);

	glBegin(GL_LINE_STRIP);
	glVertex3f(projectile.r.x, projectile.r.y, 0.0);
	glVertex3f(v.x, v.y, 0.0);
	glEnd();
}

void Tute3::draw()
{
	GLenum err;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxis(0, 0, 0, 1);

	if (cartesianMode)
		drawCircleCartesian(Vector3(projectile.r.x, projectile.r.y, 0.01), 0.05, 50);
	else
		drawCirecleParametric(Vector3(projectile.r.x, projectile.r.y, 0.01), 0.05, 50);

	drawVelocity();
	drawParabola(50);

	glutSwapBuffers();

	// Check for errors
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("%s\n", gluErrorString(err));
}

void Tute3::end()
{

}

void Tute3::drawAxis(const float &x, const float &y, const float &z, const float &size)
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

void Tute3::drawCircleCartesian(const Vector3 &pos, const float &radius, const int &steps)
{
	float x = -radius;
	float xS = 2 * radius / steps;
	float y = pos.y;

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= steps; ++i)
	{
		y = pos.y + sqrtf(radius * radius - x * x);
		glVertex3f(pos.x + x, y, 0.1);
		x += xS;
	}
	for (int i = 0; i <= steps; ++i)
	{
		y = pos.y - sqrtf(radius * radius - x * x);
		glVertex3f(pos.x + x, y, 0.1);
		x -= xS;
	}
	glEnd();
}

void Tute3::drawCirecleParametric(const Vector3 &pos, const float &radius, const int &steps)
{
	float x, y, t;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= steps; ++i)
	{
		t = (i / (float)steps) * 2 * KG_PI;
		x = radius * cosf(t);
		y = radius * sinf(t);
		glVertex3f(pos.x + x, pos.y + y, pos.z);
	}
	glEnd();
}

void Tute3::drawLine(Vector3 &pos, const Vector3 &to, const bool &normalise)
{
	glColor3f(1.0, 1.0, 0.0);

	Vector3 d;

	if (normalise)
	{
		d = to - pos;
		d.normalise();
	}
	else
		d = to;

	glBegin(GL_LINE_STRIP);
	pos.glPoint();
	d.glPoint();
	glEnd();
}