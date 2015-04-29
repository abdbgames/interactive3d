#include "stdafx.h"
#include "platformInclude.h"
#include "frog.h"
#include "keyboard.h"

void Frog::init()
{
	m_radius = 0.2f;
	m_rotSpeed = 103.2f;
	m_angle = 0.0f;
	m_inAir = false;
	//remakeSphere(10, m_radius);
}

void Frog::update(const float &deltaT)
{
	// When the frog is not in the air:
	if (!m_inAir)
	{
		// Get rotation input:
		if (kg::keyboardControl::poll(KGkey_left, KG_PRESSED))
			m_angle -= m_rotSpeed * deltaT;
			
		if (kg::keyboardControl::poll(KGkey_right, KG_PRESSED))
			m_angle += m_rotSpeed * deltaT;
			
		// Keep angle in range (6.28318f is 360 degrees in radians):
		kg::range<float>(m_angle, 0.0f, 6.28318f);
	
		// Try grabbing spacebar input:
		if (kg::keyboardControl::poll(KGkey_space, KG_DOWN))
			// Start jump:
			m_inAir = true;
	
		// Make sure frog is on the ground:
		if (m_pos.y - m_radius < 0.0f)
			m_pos.y = m_radius;
		
		// Early return:
		return;
	}
	
	// Frog is in air:
	
}

void Frog::draw()
{
	// Set colour:
	glColor3f(1.0f, 1.0f, 0.0f);
	
	// Set position:
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
	
	// Draw frog:
	/*glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		glNormal3fv(points[i].getV());
		++i;
		glVertex3fv(points[i].getV());
	}
	glEnd();*/
	
	// TODO: Fix own sphere calculation:
	glutSolidSphere(m_radius, 10, 10);
	kg::drawAxis(0.5f);
	
	// We are done so pop the matrix position:
	glPopMatrix();
}

void Frog::remakeSphere(const int &detail, const float &radius)
{
	// Clear list:
	points.clear();
	
	// Work out stepTheta and stepPhi:
	float stepTheta = 2.0f * KG_PI / detail,
		stepPhi = KG_PI / detail;
	
	// Start stacks loop:
	for (int i = 0; i < detail; ++i)
	{
		// Calculate phi:
		float phi = i / (float)detail * KG_PI;
		
		// Start Slices loop:
		for (int j = 0; j < detail; ++j)
		{
			// Calculate theta:
			float theta = j / (float)detail * 2.0f * KG_PI;
			
			// Add points and normals to the vertex/normals list:
			points.push_back(Vector3(
				sinf(phi) * cosf(theta),
				sinf(phi) * sinf(theta),
				cosf(phi)));
			points.push_back(Vector3(
				radius * sinf(phi) * cosf(theta),
				radius * sinf(phi) * sinf(theta),
				radius * cosf(phi)));
			points.push_back(Vector3(
				sinf(phi) * cosf(theta + stepTheta),
				sinf(phi) * sinf(theta + stepTheta),
				cosf(phi)));
			points.push_back(Vector3(
				radius * sinf(phi) * cosf(theta + stepTheta),
				radius * sinf(phi) * sinf(theta + stepTheta),
				radius * cosf(phi)));
			points.push_back(Vector3(
				sinf(phi + stepPhi) * cosf(theta + stepTheta),
				sinf(phi + stepPhi) * sinf(theta + stepTheta),
				cosf(phi + stepPhi)));
			points.push_back(Vector3(
				radius * sinf(phi + stepPhi) * cosf(theta + stepTheta),
				radius * sinf(phi + stepPhi) * sinf(theta + stepTheta),
				radius * cosf(phi + stepPhi)));
			points.push_back(Vector3(
				sinf(phi + stepPhi) * cosf(theta),
				sinf(phi + stepPhi) * sinf(theta),
				cosf(phi + stepPhi)));
			points.push_back(Vector3(
				radius * sinf(phi + stepPhi) * cosf(theta),
				radius * sinf(phi + stepPhi) * sinf(theta),
				radius * cosf(phi + stepPhi)));
		}
	}
}

