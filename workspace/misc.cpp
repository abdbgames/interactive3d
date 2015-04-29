#include "stdafx.h"
#include "platformInclude.h"
#include "vectors.h"
#include "ass2.h"

namespace kg
{	
	void drawAxis(const Vector3 &pos, const float &size)
	{
		// If axis drawing is disabled, son't worry about this call:
		if (!Ass2::drawAxis)
			return;
		
		// Make sure lighting is disabled:
		glDisable(GL_LIGHTING);
		
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
		
		// Enable lighting again if it was before:
		if (Ass2::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
	}
	
	void drawAxis(const float &size)
	{
		if (!Ass2::drawAxis)
			return;
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, size, 0.0f);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, size);
		glEnd();
		if (Ass2::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
	}
}

