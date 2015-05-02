#include "platformInclude.h"
#include "camera.h"
#include "mouse.h"
#include "ass2.h"

void Camera::init()
{
	m_speed = 0.25f; // Mouse sensitivity.
	m_pos.z = -1.0f;
	m_pos.y = 1.0f;
	m_dist = 3.1f;
	m_angle = 0.0f;
	m_angleY = 0.234f;
	updateBoom();
}

void Camera::updateBoom()
{
	// Set the position of the camera based on the distance and rotation from
	m_pos.x = m_origin->x - m_dist * cos(m_angleF) * cosf(m_angleY);
	m_pos.y = m_origin->y + m_dist * sinf(m_angleY);
	m_pos.z = m_origin->z - m_dist * sin(m_angleF) * cosf(m_angleY);
}

void Camera::update(const float &deltaT)
{
	if (kg::mouseControl::poll(GLUT_LEFT_BUTTON, KG_PRESSED))
		m_dist += (float)kg::mouseControl::pollMouseMoved()[1] * m_speed
			* deltaT;
	
	if (kg::mouseControl::poll(GLUT_RIGHT_BUTTON, KG_PRESSED))
	{
		m_angleY -= (float)kg::mouseControl::pollMouseMoved()[1] * m_speed
			* deltaT;
		m_angle += (float)kg::mouseControl::pollMouseMoved()[0] * m_speed
			* deltaT;
	}
	
	m_angleF = m_angle + *m_baseAngle;
	
	// Keep angles between 0 and 360 degrees (in radians):
	kg::range<float>(m_angleF, 0.0f, 6.28318f);
	
	// Hard clamp y angle and distance (3.1416f is 180 degrees in radians):
	kg::clamp<float>(m_angleY, 0.0f, 3.1416f);
	kg::clamp<float>(m_dist, 0.65f, 5.7f);
	
	updateBoom();
}

void Camera::draw()
{
	// Set up camera position and perspective:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set up perspective Matrix:
	gluPerspective(75, *m_aspect, 0.1f, 1000);
	
	// Set up "look at" Matrix:
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, // Camera position.
		m_origin->x, m_origin->y, m_origin->z, // Origin (lookAt position).
		0, 1, 0); // Up vector, positive y is up (in case that wasn't obvious).
	
	// Go back to using world matrix and ready an identity matrix:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

