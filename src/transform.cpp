#include "transform.h"
#include "engine.h"
#include "misc.h"

namespace kg
{
	void Transform2D::update()
	{
		m_vel.x = m_speed * cosf(m_angle);
		m_vel.y = m_speed * sinf(m_angle);

		if (!m_freezePos)
			m_pos = m_pos + m_vel * Engine::getDeltaTime();
	}

	void Transform2D::glStuff()
	{
		glScalef(m_scale.x, m_scale.y, 1.0f);

		glTranslatef(m_pos.x, m_pos.y, 0.0f);

		if (!m_freezeAngle)
			glRotatef(radToDeg(m_angle), 1.0f, 0.0f, 0.0f);
	}

	void Transform::update()
	{
		// This is pretty hackily taken from my last assignment, it's mainly
		// catered towards the frog, but will work well enough with the other
		// objects:
		m_vel.x = m_speed * cosf(m_rot.x) * cosf(m_rot.y);
		m_vel.y = m_speed * sinf(m_rot.y);
		m_vel.z = m_speed * sinf(m_rot.x) * cosf(m_rot.y);

		if (!m_freezePos)
			m_pos = m_pos + m_vel * Engine::getDeltaTime();
	}

	void Transform::glStuff()
	{
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glTranslatef(m_pos.x, m_pos.y, m_pos.z);

		if (!m_freezeRotX)
			glRotatef(radToDeg(m_rot.x), 1.0f, 0.0f, 0.0f);
		if (!m_freezeRotY)
			glRotatef(radToDeg(m_rot.y), 0.0f, 1.0f, 0.0f);
		if (!m_freezeRotZ)
			glRotatef(radToDeg(m_rot.z), 0.0f, 0.0f, 1.0f);
	}
}

