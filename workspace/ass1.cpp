#include "stdafx.h"
#include "ass1.h"
#include "keyboard.h"

void Ass1::init()
{
	// Initialise starting values:
	frogPos = frogPosI = Vector2(0, 0);
	frogVel = frogVelI = Vector2(1, 2);

	m_debug = m_drawTangents = m_drawNormals = m_analytical = true;
	frogInAir = m_paraCart = m_circleCart = false;

	m_radius = 0.05f;
	m_dir = m_keySpeed = m_speed = m_dist = 1.0f;
	m_sT = glutGet(GLUT_ELAPSED_TIME) / (float)milli;

	m_paraSteps = m_circleSteps = 20;

	screenLeft = -1.0f;
	screenRight = 1.0f;

	// Reserve vector size to ensure auto resizing does not occur until needed:
	m_circlePoints.reserve(m_circleSteps);

	// Create our first circle depending on if we want parametric or cartesian:
	(m_circleCart) ? updateCircleCartesian() : updateCircleParametric();
}

void Ass1::updateTime()
{
	// Update time parameters:
	static float lastT = -1.0;

	m_t = glutGet(GLUT_ELAPSED_TIME) / (float)milli - m_sT;

	if (lastT < 0.0)
	{
		lastT = m_t;
		return;
	}

	m_dT = m_t - lastT;

	// Debugging:
	//if (m_debug)
		//printf("Time: %f; DeltaTime: %f;\n", m_t, m_dT);

	lastT = m_t;
}

void Ass1::update()
{
	/* KeyBufferBegin and keyBufferEnd need to be called, because of the
	 * way key handling works as callback functions, the source for these
	 * functions are commented, so look there if you must see what they do :P */
	kg::keyboardControl::keyBufferBegin();

	// Update time:
	updateTime();

	// Save on unnecesary draw calls:
	bool shouldDraw = false;

	// Key toggles:
	if (kg::keyboardControl::onKeyPress(KGkey_t))
	{
		// Toggle tangent drawing:
		if (m_debug)
			printf("Toggled tangent drawing %s.\n", (m_drawTangents) ? "off" : "on");

		shouldDraw = true;

		m_drawTangents = !m_drawTangents;
	}

	if (kg::keyboardControl::onKeyPress(KGkey_n))
	{
		// Toggle normal drawing:
		if (m_debug)
			printf("Toggled normal drawing %s.\n", (m_drawNormals) ? "off" : "on");

		shouldDraw = true;

		m_drawNormals = !m_drawNormals;
	}

	if (kg::keyboardControl::onKeyPress(KGkey_y))
	{
		// Toggle debugging:
		printf("Toggled debugging %s.\n", (m_debug) ? "off" : "on");

		m_debug = !m_debug;
	}

	if (kg::keyboardControl::onKeyPress(KGkey_i))
	{
		// Toggle analytical/numerical:
		if (m_debug)
			printf("Toggled %s mode.\n", (m_analytical) ? "numetrical" : "analytical");

		m_analytical = !m_analytical;
	}

	// Circle/Parabola segment control:
	if (kg::keyboardControl::onKeyPress(KGkey_2))
	{
		if (m_circleSteps > 1000000)
		{
			printf("Doubling Circle segments to: %d.\n", m_circleSteps);
			m_circleSteps *= 2;
			(m_circleCart) ? updateCircleCartesian() : updateCircleParametric();
			shouldDraw = true;
		}
		else
			printf("Warning: cannot increase segments anymore!");
	}

	if (kg::keyboardControl::onKeyPress(KGkey_1))
	{
		if (m_circleSteps > 2)
		{
			printf("Halving Circle segments to: %d.\n", m_circleSteps);
			m_circleSteps /= 2;
			(m_circleCart) ? updateCircleCartesian() : updateCircleParametric();
			shouldDraw = true;
		}
		else
			printf("Warning: cannot reduce segments anymore!");
	}

	// Only redo frog velocity if frog is not in air:
	if (!frogInAir)
	{
		// Save on updating velocity if we don't input anything:
		bool hasChanged = false;

		// Shift direction on keyboard input (clamping rotation to stay above y:0):
		if (kg::keyboardControl::onKeyPressed(KGkey_a))
		{
			hasChanged = true;

			// 3.1416 is 180 degrees in radians:
			if (m_dir < 3.1416f)
				m_dir += m_keySpeed * m_dT;
			else
				m_dir = 3.1416f;
		}

		if (kg::keyboardControl::onKeyPressed(KGkey_d))
		{
			hasChanged = true;

			// 0 degrees and 0 radians are the same angle:
			if (m_dir > 0.0f)
				m_dir -= m_keySpeed * m_dT;
			else
				m_dir = 0.0f;
		}

		// Shift speed on keyboard input:
		if (kg::keyboardControl::onKeyPressed(KGkey_w))
		{
			hasChanged = true;
			m_speed += m_keySpeed * m_dT;
		}

		if (kg::keyboardControl::onKeyPressed(KGkey_s))
		{
			hasChanged = true;
			m_speed -= m_keySpeed * m_dT;
		}

		// Jumping:
		if (kg::keyboardControl::onKeyPress(KGkey_space))
		{
			// Set time:
			m_sT = glutGet(GLUT_ELAPSED_TIME) / (float)milli;

			// Set frog in air flag:
			frogInAir = true;

			// Debugging:
			if (m_debug)
				printf("Frog jumped.\n");
		}

		// Reset initial velocity if we need to:
		if (hasChanged)
		{
			// Reset velocity vector (Euler intergration):
			frogVelI.x = cosf(m_dir) * m_speed;
			frogVelI.y = sinf(m_dir) * m_speed;

			// Debugging:
			if (m_debug)
				printf("Speed: %f; Dir (rad): %f; Dir (deg): %f;\n",
				m_speed, m_dir, m_dir * 180 / KG_PI);

			// Redraw since the velocity/speed changed:
			shouldDraw = true;
		}
	}
	else
	{
		// Calculate and update the frogs next position:
		if (m_analytical)
		{
			// Store 1/2 * g to save on multiplications:
			static float preCalc = 0.5 * -KG_GR;
			frogPos.x = frogVelI.x * m_t + frogPosI.x;
			frogPos.y = m_t * (preCalc * m_t + frogVelI.y) + frogPosI.y;
		}
		else
		{
			// Position:
			frogPos.x += frogVel.x * m_dT;
			frogPos.y += frogVel.y * m_dT;

			// Velocity:
			frogVel.y -= KG_GR * m_dT;
		}

		// if our frog hit's y:0 or lower:
		if (frogPos.y < 0.0f)
		{
			// Make it so we can jump, and we are no longer 'in air':
			frogInAir = false;

			// Make sure the position stays at y:0:
			frogPos.y = 0.0f;

			// Set the initial to current position:
			frogPosI = frogPos;
		}

		// Redraw since our frog is moving:
		shouldDraw = true;
	}

	// If we are allowed to draw on this update, send our callback request:
	if (shouldDraw)
		glutPostRedisplay();

	kg::keyboardControl::keyBufferEnd();
}

void Ass1::updateCircleCartesian()
{
	/* Adds the coordinates for a catesian circle to a list. */
	// First clear list:
	m_circlePoints.clear();

	// Start x at the negative of the radius
	// (it will loop through to positive radius):
	float x = -m_radius;
	// Gets the x interval to add by:
	// The division and multiplcation saves on rounding errors later:
	float xS = 2 * m_radius / (m_circleSteps / 2) * 2;
	// The y position:
	float y;

	// Start the upper circle loop:
	for (int i = 0; i <= m_circleSteps / 2; ++i)
	{
		// Set y:
		y = sqrtf(m_radius * m_radius - x * x);

		// Add circle point to the end of the list:
		m_circlePoints.push_back(Vector3(x, y));

		// Incriment x:
		x += xS;
	}
	// Start the lower circle loop:
	for (int i = 0; i <= m_circleSteps / 2; ++i)
	{
		// This does the same as the previous loop to a negative y value:
		y = -(sqrtf(m_radius * m_radius - x * x));
		m_circlePoints.push_back(Vector3(x, y, 0.1));
		x -= xS;
	}
}

void Ass1::updateCircleParametric()
{
	float t;

	// Start looping over circle steps:
	for (int i = 0; i <= m_circleSteps; ++i)
	{
		// Work out t value:
		t = (i / (float)m_circleSteps) * 2 * KG_PI;
		// Push to back of our points list:
		m_circlePoints.push_back(Vector3(m_radius * cosf(t), m_radius * sinf(t)));
	}
}

void Ass1::draw()
{
	// Clear screen:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Allow depth buffering:
	glEnable(GL_DEPTH_TEST);

	// Draw axis:
	drawAxis(Vector3(0, 0, 0), 1);

	// Draw frog depending on draw mode:
	drawCircle();

	// Draw parabola based on parametric or cartesian mode:
	(m_paraCart) ? drawParabolaCartesian() : drawParabolaParametric();

	// Draw line for velocity:
	if (!frogInAir)
		drawLine(Vector3(frogPos), Vector3(frogPos + frogVelI / 5.5f), Vector3(1, 0, 1));

	// Swap buffers:
	glutSwapBuffers();
}

void Ass1::drawAxis(const Vector3 &pos, const float &size)
{
	// Set the colour and set points for the lines that make our axis:
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos.x + size, pos.y, pos.z);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos.x, pos.y + size, pos.z);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos.x, pos.y, pos.z + size);
	glEnd();
}

void Ass1::drawCircle()
{
	// Set the colour to white:
	glColor3f(1.0, 1.0, 1.0);

	// Begin drawing a line loop:
	glBegin(GL_LINE_LOOP);
	// Loop over stored points:
	for (unsigned int i = 0; i < m_circlePoints.size(); ++i)
	{
		// Temporary Vector for getting true position of points:
		Vector3 t(frogPos + m_circlePoints[i]);
		// Vector as GLVertex:
		t.glPoint();
	}
	// End drawing:
	glEnd();

	// Loop again to draw tangents/normals:
	if (m_drawTangents || m_drawNormals)
	{
		for (unsigned int i = 0; i < m_circlePoints.size(); ++i)
		{
			// Temporary Vector for getting true position of points:
			Vector3 start(frogPos + m_circlePoints[i]);
			Vector3 end;

			if (m_drawTangents)
			{
				end = Vector3(1.0f, (-m_circlePoints[i].x / m_circlePoints[i].y));
				end.normalise();
				end = end * m_radius;
				drawLine(start, start + end, Vector3(1.0f, 1.0f, 0.0f));
			}
			if (m_drawNormals)
			{
				end = Vector3(m_circlePoints[i].x, m_circlePoints[i].y);
				end.normalise();
				end = end * m_radius;
				drawLine(start, start + end, Vector3(1.0f, 1.0f, 0.0f));
			}
		}
	}
}

void Ass1::drawParabolaCartesian()
{
	
}

void Ass1::drawParabolaParametric()
{
	// Set colour depending on air status:
	(frogInAir) ? glColor3f(1.0, 0.0, 0.0) : glColor3f(0.0, 1.0, 0.0);

	// Work out initial variables:
	float flightTime = (2.0 * m_speed * sinf(m_dir)) / KG_GR, x, y,
		in = flightTime / (float)m_paraSteps,
		preCalc = (1 / (float)2) * -KG_GR, t;

	// Work out direction:
	bool isLeft = (frogVelI.x < 0.0f);

	glBegin(GL_LINE_STRIP);
	glVertex3f(frogPos.x, frogPos.y, 0.0);
	for (int i = 1; i <= m_paraSteps; ++i)
	{
		t = i * in;
		x = frogVelI.x * t + frogPosI.x;
		// If our frog is ahead of our parabola, don't bother drawing it:
		if ((isLeft && x > frogPos.x) || (!isLeft && frogPos.x > x))
			continue;
		y = (preCalc * t * t) + (frogVelI.y * t) + frogPosI.y;
		glVertex3f(x, y, 0.0);
	}
	glEnd();
}


void Ass1::drawLine(Vector3 &pos, Vector3 &to, const Vector3 &colour)
{
	// Set the colour:
	glColor3f(colour.x, colour.y, colour.z);
	// Draw a line from two Vector points:
	glBegin(GL_LINE_STRIP);
	pos.glPoint();
	to.glPoint();
	glEnd();
}