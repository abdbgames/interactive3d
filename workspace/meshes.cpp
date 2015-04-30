#include "stdafx.h"
#include "meshes.h"

CarMesh *CarMesh::m_instance = NULL;

CarMesh *CarMesh::get()
{
	return (m_instance) ? m_instance : new CarMesh();
}

CarMesh::CarMesh()
{
	//gluQuad = gluNewQuadric();
}
	
CarMesh::~CarMesh()
{
	//gluDeleteQuadric(gluQuad);
}

void CarMesh::draw()
{
	// TODO: Vertex buffer for car:
	glColor3f(0.83f, 0.0f, 0.12f);
	glutSolidCube(1.0f);
}

LogMesh *LogMesh::m_instance = NULL;

LogMesh *LogMesh::get()
{
	return (m_instance) ? m_instance : new LogMesh();
}

LogMesh::LogMesh()
{
	gluQuad = gluNewQuadric();
}
	
LogMesh::~LogMesh()
{
	gluDeleteQuadric(gluQuad);
}

void LogMesh::draw()
{
	// TODO: Vertex buffer for log:
	glColor3f(0.2f, 0.1f, 0.0f);
	gluCylinder(gluQuad, 1.0f, 1.0f, 2.0f, 20, 30);
}

