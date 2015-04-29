#include "stdafx.h"
#include "ass2.h"
#include "keyboard.h"

int Ass2::m_width = 1024, Ass2::m_height = 768;
float Ass2::m_aspect = 1.333333333f;

void Ass2::init()
{
	m_sT = 0.0f;
	m_debug = false;
	m_camera.updateSize(&m_aspect);
	m_camera.updateOrigin(m_frog.getPos());
	m_frog.init();
	m_camera.init();
	m_floor.init();
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
	
	// If we are debugging print the stack of any keys pressed before this
	// update call:
	if (m_debug)
	{
		if (kg::keyboardControl::pollAny(KG_DOWN))
		{
			printf("Key(s) pressed before this update call: ");
			for (unsigned int i = 0;
				i < kg::keyboardControl::getPressBuffer().size(); ++i)
					printf("%c ", kg::keyboardControl::getPressBuffer()[i]);
		
			printf("\n");
		}
	}
	
	// Handle keyboard input:
	if (kg::keyboardControl::poll(KGkey_q, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_Q, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_esc, KG_DOWN))
			// Quit the program:
			exit(EXIT_SUCCESS);
	
	m_frog.update(m_dT);
	m_camera.update(m_dT);
	
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

	// "Draw" our camera, this set's up the scene to look as if it was being
	// looked at by the camera object:
	m_camera.draw();

	// Draw axis:
	drawAxis(Vector3(0, 0, 0), 1);
	
	m_frog.draw();
	m_floor.draw();

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

void Ass2::grabSize(int w, int h)
{
	// Set local width/height:
	m_width = w;
	m_height = h;
	
	// Set aspect:
	m_aspect = (float)w/(float)h;
	
	// Reset viewport:
	glViewport(0, 0, w, h);
}

