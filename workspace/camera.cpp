#include "stdafx.h"
#include "platformInclude.h"
#include "camera.h"
#include "mouse.h"

void Camera::init()
{
	m_speed = 0.9f;
	m_pos.z = -1.0f;
	m_pos.y = 1.0f;
	m_dist = 3.1f;
	m_angle = 0.0f;
	updateBoom();
}

void Camera::updateBoom()
{
	// Set the position of the camera based on the distance and rotation from
	// the origin: TODO: Camera y rotation (look at frog vector calculation):
	m_pos.x = m_origin->x + m_dist * cos(m_angle);
	m_pos.z = m_origin->z - m_dist * sin(m_angle);
}

void Camera::update(const float &deltaT)
{

	if (kg::mouseControl::poll(GLUT_LEFT_BUTTON, KG_PRESSED))
		m_dist += (float)kg::mouseControl::pollMouseMoved()[1] * m_speed
			* deltaT;
	
	if (kg::mouseControl::poll(GLUT_RIGHT_BUTTON, KG_PRESSED))
		m_angle += (float)kg::mouseControl::pollMouseMoved()[0] * m_speed
			* deltaT;
		
	kg::range<float>(m_angle, 0.0f, 6.28318f);
	
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

