#include "stdafx.h"
#include "platformInclude.h"
#include "floor.h"

Floor::~Floor()
{
	delete [] points;
	points = NULL;
}

void Floor::init()
{
	points = NULL;
	buildFloor(Vector2(2.0f, 2.0f), Vector3(10.0f, 0.0f, 10.0f), 10, 10);
}

void Floor::update(const float &deltaT)
{
	
}

void Floor::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < indices.size(); ++i)
	{
		glNormal3f(0, 1, 0);
		glVertex3fv(points[indices[i]].getV());
	}
	glEnd();
}

void Floor::buildFloor(const Vector2 &scale, const Vector3 &pos,
		const int &rows, const int &columns)
{
	if (points)
		delete [] points;
	
	indices.clear();
	
	points = new Vector3[rows * columns];
	
	// Build a grid of vertex points:
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < columns; ++j)
		{
		    points[j + (i * rows)] = Vector3((scale.x * (float)j) - pos.x,
		    	pos.y,
		    	(scale.y * (float)i) - pos.z);
		}
	}
	
	// Build an index list to access those vertcies in an order to make a
	// valid triangle strip:
	for (int i = 0; i < rows-1; ++i)
	{
		if (i != 0)
			indices.push_back(i * rows);
		
		for (int j = 0; j < columns; ++j)
		{
			indices.push_back(i * columns + j);
			indices.push_back((i + 1) * columns + j);
		}
		
		if (i != (rows-2))
			indices.push_back((i + 1) * rows + (columns - 1));
	}
}

