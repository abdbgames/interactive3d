#include "object.h"
#include <cmath>

Object::~Object()
{
	if (m_ambient) delete [] m_ambient;
	if (m_diffuse) delete [] m_diffuse;
	if (m_specular) delete [] m_specular;
	if (m_shininess) delete m_shininess;
}

void Object::setDir(const float &dir)
{
	// From an angle value in radians, calculate and set our rotation vector:
	m_dir.x = cosf(dir);
	m_dir.y = sinf(dir);
}

