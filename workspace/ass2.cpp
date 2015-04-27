#include "stdafx.h"
#include "ass2.h"
#include "keyboard.h"

void Ass2::init()
{
	m_sT = 0.0f;
	m_debug = false;
	m_frog.init();
}

void Ass2::updateTime()
{
	// Update time parameters:
	static float lastT = -1.0;

	m_t = glutGet(GLUT_ELAPSED_TIME) / (float)milli;

	if (lastT < 0.0)
	{
		lastT = m_t;
		return;
	}

	m_dT = m_t - lastT;

	// Debugging:
	if (m_debug)
		printf("Time: %f; DeltaTime: %f;\n", m_t, m_dT);

	lastT = m_t;
}

void Ass2::update()
{
	// Update time:
	updateTime();
	
	// If we are hitting a mouse button, lock the mouse to that position and
	// hide the cursor, otherwise unlock and set cursor to "clickable":
	if (kg::mouseControl::pollAny(KG_PRESSED))
	{
		// The locking itself always occurs at the end of an update, so it's
		// safe to put this call anywhere:
		kg::mouseControl::lockMouse(kg::mouseControl::m_x,
			kg::mouseControl::m_y);
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		kg::mouseControl::unlockMouse();
		glutSetCursor(GLUT_CURSOR_INFO);
	}
	
	if (kg::keyboardControl::pollAny(KG_PRESSED))
	{
		printf("Key(s) pressed before this update call: ");
		for (unsigned int i = 0; i < kg::keyboardControl::getBuffer().size();
			++i)
		{
			printf("%c ", kg::keyboardControl::getBuffer()[i]);
		}
		
		printf("\n");
	}
	
	m_frog.update();
	
	// Draw callback:
	glutPostRedisplay();

	// Start polling for input callbacks:
	kg::keyboardControl::postUpdate();
	kg::mouseControl::postUpdate();
}

void Ass2::draw()
{
	// Clear screen:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Allow depth buffering:
	glEnable(GL_DEPTH_TEST);

	// Draw axis:
	drawAxis(Vector3(0, 0, 0), 1);
	
	m_frog.draw();

	// Swap buffers:
	glutSwapBuffers();
}

void Ass2::drawAxis(const Vector3 &pos, const float &size)
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

