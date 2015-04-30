#include "stdafx.h"
#include "platformInclude.h"
#include "car.h"
#include "ass2.h"
#include "meshes.h"

void Car::init()
{
	
}

void Car::update(const float &deltaT)
{
	// Move and warp at the edge:
	m_pos.z += m_vel.z * deltaT;	
	kg::range(m_pos.z, -50.1f, 50.1f);
}

void Car::draw()
{
	// Set position:
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	
	if (isCar)
	{
		CarMesh::get()->draw();
	}
	else
	{
		LogMesh::get()->draw();
	}
	
	// We are done so pop the matrix position:
	glPopMatrix();
}

