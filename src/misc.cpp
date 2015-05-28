// Program uses the Simple OpenGL Image Library for loading textures:
// http://www.lonesock.net/soil.html
#include <SOIL.h>
#include <cstdio>
#include <cstdlib>

#include "platformInclude.h"
#include "misc.h"
#include "engine.h"

namespace kg
{
	float lerpf(const float &from, const float &to, const float &delta)
	{
		// Safe lerp:
		return (1.0f - delta) * from + delta * to;
	}

	float degToRad(const float &in)
	{
		// Returns the angle in degrees converted to radians:
		return in / (KG_PI / 180.0f);
	}

	float radToDeg(const float &in)
	{
		// Returns the angle in radians converted to degrees:
		return in * (180.0f / KG_PI);
	}

	void clampDeg(float &in)
	{
		// Clamps variable between 0 and 360 degrees:
		clamp(in, 0.0f, 360.0f);
	}

	void clampRad(float &in)
	{
		// Clamps variable between 0 and 360 degrees as radians:
		clamp(in, 0.0f, (float)(KG_PI * 2.0f));
	}

	void drawAxis(const Vector3 &pos, const float &size)
	{
		// If axis drawing is disabled, son't worry about this call:
		if (!Engine::getDrawAxisEnabled())
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
		if (Engine::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
	}

	void drawAxis(const float &size)
	{
		if (!Engine::getDrawAxisEnabled())
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

		if (Engine::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
	}

	void drawNormal(Vector3 &from, Vector3 &to)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3fv(from.getV());
		glVertex3fv(to.getV());
		glEnd();

		if (Engine::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
	}

	// Texture loading from sample texture viewer application:
	GLuint loadTexture(const char *filename)
	{
		GLuint tex = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

		if (!tex)
		{
			printf("Failed to load: \"%s\".\n", filename);
			return 0;
		}

		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glBindTexture(GL_TEXTURE_2D, 0);

		return tex;
	}
}
