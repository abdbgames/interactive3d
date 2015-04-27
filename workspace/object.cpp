#include "object.h"
#include <math.h>

void Object::setDir(const float &dir)
{
	// From an angle value in radians, calculate and set our rotation vector:
	m_dir.x = cos(dir);
	m_dir.y = sin(dir);
}

