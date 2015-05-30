#include "camera.h"
#include "engine.h"
#include "misc.h"

namespace kg
{
	void Camera::modelViewGL()
	{
		// nice sample code you got here ;)
		// Uploads the camera's tansforms to the modelview matrix.
		// Call this before doing any other rendering and you
		// can position your geometry in the world without having to worry
		// about the camera at all.
		glLoadIdentity();

		if (m_zoom > 0.0f)
		{
			// Translation won't work if this isn't in perspective mode,
			// in which case scale needs to be used instead.
			if (m_perspective)
				glTranslatef(0.0f, 0.0f, -m_zoom);
			else
				glScalef(1.0f / m_zoom, 1.0f / m_zoom, 1.0f);
		}

		glTranslatef(-m_pos.x, -m_pos.y, -m_pos.z);
		glRotatef(m_rot.x, 1, 0, 0);
		glRotatef(m_rot.y, 0, 1, 0);

		if (m_lookAt)
			glTranslatef(-m_lookAt->x, -m_lookAt->y, -m_lookAt->z);
	}

	void Camera::projectionGL()
	{
		// Fairly standard projection matrix,
		// can be either perspective or orthographic:
		glViewport(0, 0, Engine::getWidth(), Engine::getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (m_perspective)
			gluPerspective(m_fov, Engine::getAspect(), m_near, m_far);
		else
			glOrtho(0.0f, (float)Engine::getWidth(), 0.0f,
			(float)Engine::getHeight(), 0.0f, m_far);

		glMatrixMode(GL_MODELVIEW);
	}

	void Camera::updateRot(const int &dx, const int &dy)
	{
		// Rotates the camera using horizontal and vertical mouse movement.
		m_rot.x += dx * m_sensitivity * Engine::getDeltaTime();
		m_rot.y += dy * m_sensitivity * Engine::getDeltaTime();

		keepDegRange(m_rot.y);
		clamp(m_rot.x, 1.278f, 88.73f);
	}

	void Camera::updateZoom(const int &dy)
	{
		// Zooms the camera using vertical mouse movement.
		m_zoom -= dy * m_zoom * m_sensitivity * Engine::getDeltaTime() * 0.1f;
		clamp(m_zoom, m_near, m_far / 2.0f);
	}

	const Vector3 &Camera::getCamPos()
	{
		// Camera world pos:
		Vector3 pos = m_pos;

		if (m_lookAt)
			pos = pos + *m_lookAt;

		pos.x += sinf(degToRad(m_rot.y)) * m_zoom;
		pos.z += cosf(degToRad(m_rot.y)) * m_zoom;
		pos.y += sinf(degToRad(m_rot.x)) * m_zoom;

		pos.x = -pos.x;

		return pos;
	}
}
