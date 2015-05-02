#include "platformInclude.h"
#include "frog.h"
#include "keyboard.h"
#include "ass2.h"

void Frog::init()
{
	m_radius = 0.3f;
	m_speed = 4.0f;
	m_rotSpeed = 1.2f;
	m_angle.y = 0.7854f; // 45 degrees in radians.
	m_angle.x = 0.7854f;
	m_pSteps = 30;
	m_cDetail = 30;
	m_inAir = false;
	//remakeSphere(10, m_cDetail);
	
	m_ambient = new GLfloat[4];
	m_ambient[0] = 1.0f;
	m_ambient[1] = 1.0f;
	m_ambient[2] = 0.0f;
	m_ambient[3] = 1.0f;
	
	m_diffuse = m_ambient;
	
	m_specular = new GLfloat[4];
	m_specular[0] = 1.0f;
	m_specular[1] = 1.0f;
	m_specular[2] = 1.0f;
	m_specular[3] = 1.0f;
	
	m_shininess = new GLfloat;
	*m_shininess = 70;
}

void Frog::update(const float &deltaT)
{
	// When the frog is not in the air:
	if (!m_inAir)
	{
		// Get rotation input:
		if (kg::keyboardControl::poll(KGkey_left, KG_PRESSED))
			m_angle.x -= m_rotSpeed * deltaT;
			
		if (kg::keyboardControl::poll(KGkey_right, KG_PRESSED))
			m_angle.x += m_rotSpeed * deltaT;
		
		if (kg::keyboardControl::poll(KGkey_a, KG_PRESSED) ||
			kg::keyboardControl::poll(KGkey_A, KG_PRESSED))
			m_angle.y += m_rotSpeed * deltaT;
			
		if (kg::keyboardControl::poll(KGkey_d, KG_PRESSED) ||
			kg::keyboardControl::poll(KGkey_D, KG_PRESSED))
			m_angle.y -= m_rotSpeed * deltaT;
			
		if (kg::keyboardControl::poll(KGkey_w, KG_PRESSED) ||
			kg::keyboardControl::poll(KGkey_W, KG_PRESSED))
			m_speed += m_rotSpeed * deltaT;
			
		if (kg::keyboardControl::poll(KGkey_s, KG_PRESSED) ||
			kg::keyboardControl::poll(KGkey_S, KG_PRESSED))
			m_speed -= m_rotSpeed * deltaT;
			
		// Keep x angle in range (6.28318f is 360 degrees in radians):
		kg::range<float>(m_angle.x, 0.0f, 6.28318f);
		// Hard clamp y angle and speed (3.1416f is 180 degrees in radians):
		kg::clamp<float>(m_angle.y, 0.0f, 3.1416f);
		kg::clamp<float>(m_speed, 0.0f, 8.5f);
		
		// Calculate velocity Vector, first the 2D direction, then the 3D:
		m_vel.x = m_speed * cosf(m_angle.x) * cosf(m_angle.y);
		m_vel.y = m_speed * sinf(m_angle.y);
		m_vel.z = m_speed * sinf(m_angle.x) * cosf(m_angle.y);
	
		// Try grabbing spacebar input:
		if (kg::keyboardControl::poll(KGkey_space, KG_DOWN))
			// Start jump:
			m_inAir = true;
		
		// Set the initial position:
		m_initPos = m_pos;
		m_initVel = m_vel;
		
		// Early return:
		return;
	}
	
	// Frog is in air, apply gravity and velocity:
	m_vel.y -= KG_GR * deltaT;
	m_pos.x += m_vel.x * deltaT;
	m_pos.y += m_vel.y * deltaT;
	m_pos.z += m_vel.z * deltaT;
	
	// Check if frog hit the ground:
	if (m_pos.y < 0.0f)
	{
		m_inAir = false;
		m_pos.y = 0.0f;
	}
}

void Frog::draw()
{
	// Set material properties:
	if (m_ambient)
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	if (m_diffuse)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	if (m_specular)
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	if (m_shininess)
		glMaterialfv(GL_FRONT, GL_SHININESS, m_shininess);

	// Set colour:
	glColor3f(1.0f, 1.0f, 0.0f);
	
	// Set position:
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y + m_radius, m_pos.z);
	glPushMatrix();
	// Why the f*** does this not take radians... (ง ͠° ͟ل͜ ͡°)ง:
	glRotatef(-(m_angle.x * 57.29578f), 0.0f, 1.0f, 0.0f);
	
	// Draw frog:
	/*glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		glNormal3fv(points[i].getV());
		++i;
		glVertex3fv(points[i].getV());
	}
	glEnd();*/
	
	// TODO: Fix own sphere calculation:
	glutSolidSphere(m_radius, m_cDetail, m_cDetail);
	
	// Draw axis:
	kg::drawAxis(0.5f);
	
	// Disable lighting:
	glDisable(GL_LIGHTING);
	
	// Pop the matrix for rotation:
	glPopMatrix();
	
	// Draw the velocity vector:
	glColor3f(1.0f, 0.0f, 1.0f);
	
	Vector3 vDraw = m_initVel / 5.0f;
	
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3fv(vDraw.getV());
	glEnd();
	
	// We only want to draw the parabola from the initial frog position:
	glPopMatrix();
	glPushMatrix();
	glTranslatef(m_initPos.x, m_initPos.y, m_initPos.z);
	
	// Draw the parabola:
	drawParabola();
	
	// Enable lighting again if it was before:
	if (Ass2::getLightState() != KG_UNLIT)
		glEnable(GL_LIGHTING);
	
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

void Frog::drawParabola()
{
	// Work out initial variables:
	float flightTime = (2.0f * m_speed * sinf(m_angle.y)) / KG_GR, t,
		in = flightTime / (float)m_pSteps, preCalc = 0.5f * -KG_GR;
		
	Vector2 dir(cosf(m_angle.x), sinf(m_angle.x));
	
	// Set colour depending on air status:
	(m_inAir) ? glColor3f(1.0, 0.0, 0.0) : glColor3f(0.0, 0.0, 1.0);
	
	// Work out direction:
	bool xBack = (m_initVel.x < 0.0f);
	bool zBack = (m_initVel.z < 0.0f);
	
	glBegin(GL_LINE_STRIP);
	
	// Always draw a starting point otherwise we may run into issues with
	// selectivly drawing verts:
	Vector3 v(m_pos - m_initPos);
	glVertex3fv(v.getV());
	
	// Calculation loop, adding points as we go:
	for (int i = 0; i <= m_pSteps; ++i)
	{
		t = i * in;
		Vector3 c(m_initVel.x * t, (preCalc * t * t) + (m_initVel.y * t),
			m_initVel.z * t);
	
		// Don't draw this vert if the frog has passed it:
		if (((xBack && c.x >= v.x) || (!xBack && v.x >= c.x)) &&
			((zBack && c.z >= v.z) || (!zBack && v.z >= c.z)))
			continue;
			
		glVertex3fv(c.getV());
	}
	
	glEnd();
}

