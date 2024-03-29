// Program uses the Simple OpenGL Image Library for loading textures:
// http://www.lonesock.net/soil.html
#include <SOIL.h>
#include <cstdio>
#include <cstdlib>
#include <map>

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

	void keepDegRange(float &in)
	{
		// Clamps variable between 0 and 360 degrees:
		range(in, 0.0f, 360.0f);
	}

	void keepRadRange(float &in)
	{
		// Clamps variable between 0 and 360 degrees as radians:
		range(in, 0.0f, (float)(KG_PI * 2.0f));
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

	// Texture loading from sample texture viewer application:
	GLuint &loadTexture(const char *filename)
	{
		static std::map<std::string, GLuint> textureIndex;

		static std::map<std::string, GLuint>::iterator
			i = textureIndex.find(filename);

		if (i != textureIndex.end())
			return i->second;

		textureIndex.insert(std::pair<std::string, GLuint>(filename,
			SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y)));

		GLuint &tex = textureIndex.find(filename)->second;

		if (!tex)
			printf("Failed to load: \"%s\".\n", filename);

		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glBindTexture(GL_TEXTURE_2D, tex);

		return tex;
	}
}

std::string operator +(const std::string &l, const float &r)
{
	return kgcc<float>(r, l, true);
}

std::string operator +(const float &l, const std::string &r)
{
	return kgcc<float>(l, r, false);
}

std::string operator +(const std::string &l, const int &r)
{
	return kgcc<float>(r, l, true);
}

std::string operator +(const int &l, const std::string &r)
{
	return kgcc<float>(l, r, false);
}

std::string operator +(const std::string &l, const unsigned &r)
{
	return kgcc<float>(r, l, true);
}

std::string operator +(const unsigned &l, const std::string &r)
{
	return kgcc<float>(l, r, false);
}

std::string operator +(const std::string &l, const bool &r)
{
	return l + ((r) ? "true" : "false");
}

std::string operator +(const bool &l, const std::string &r)
{
	return ((l) ? "true" : "false") + r;
}
