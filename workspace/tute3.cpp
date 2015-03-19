#include "stdafx.h"
#include "Tute3.h"
#include "keyboard.h"


bool debug = true;
bool go = false;

typedef struct { float x, y; } vec2f;
typedef struct { vec2f r0, v0, r, v; } state;
state projectile = {
		{ 0.0, 0.0 },
		{ 1.0, 2.0 },
		{ 0.0, 0.0 },
		{ 1.0, 2.0 }
};
const float g = -9.8;

float startTime;
const int milli = 1000;

typedef enum { analytical, numerical } integrationMode;
integrationMode integrateMode = numerical;

void updateProjectileStateAnalytical(float t)
{
	vec2f r0, v0;

	r0 = projectile.r0;
	v0 = projectile.v0;

	projectile.r.x = v0.x * t + r0.x;
	projectile.r.y = 1.0 / 2.0 * g * t * t + v0.y * t + r0.y;
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

}

void Tute3::update()
{
	kg::keyboardControl::keyBufferBegin();

	static float lastT = -1.0;
	float t, dt;

	if (!go)
		return;

	t = glutGet(GLUT_ELAPSED_TIME) / (float)milli - startTime;

	if (lastT < 0.0) {
		lastT = t;
		return;
	}

	dt = t - lastT;
	if (debug)
		printf("%f %f\n", t, dt);
	updateProjectileState(t, dt);
	lastT = t;

	glutPostRedisplay();

	if (kg::keyboardControl::onKeyPressed(KGkey_i))
	{
		if (integrateMode == analytical)
			integrateMode = numerical;
		else
			integrateMode = analytical;

		printf("nice meme\n");
	}

	if (kg::keyboardControl::onKeyPressed(KGkey_s) && !go)
	{
		startTime = glutGet(GLUT_ELAPSED_TIME) / (float)milli;
		go = true;
		printf("nice meme\n");
	}

	kg::keyboardControl::keyBufferEnd();
}

void displayProjectile(void)
{
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(projectile.r.x, projectile.r.y);
	glEnd();
}

void Tute3::draw()
{
	GLenum err;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.8, 0.8, 0.8);

	// Display projectile
	displayProjectile();

	glutSwapBuffers();
	// Check for errors
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("%s\n", gluErrorString(err));
}

void Tute3::end()
{

}
