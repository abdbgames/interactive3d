#include "platformInclude.h"
#include "car.h"
#include "ass2.h"
#include "meshes.h"

void Car::init()
{
	m_t = 0.0f;

	if (isCar) return;

	rotY = kg::getRandom<float>(-0.05f, 0.05f);
	rotZ = kg::getRandom<float>(-0.15f, 0.15f);
	m_rockSpeed = kg::getRandom<float>(0.07f, 2.3f);
}

void Car::update(const float &deltaT)
{
	// Move and warp at the edge:
	m_pos.z += m_vel.z * deltaT;	
	kg::range(m_pos.z, -50.1f, 50.1f);

	if (!isCar)
		m_t += deltaT * m_rockSpeed;
}

void Car::draw()
{
	// Set position:
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	
	if (isCar)
		CarMesh::get()->draw();
	else
	{
		glRotatef(sinf(m_t) * 57.29577f, 0.0f, rotY, rotZ);
		LogMesh::get()->draw();
	}
		
	// Draw axis:
	kg::drawAxis(1.5f);
	
	// We are done so pop the matrix position:
	glPopMatrix();
}

