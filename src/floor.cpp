#include "platformInclude.h"
#include "floor.h"
#include "ass2.h"

Floor::~Floor()
{
	clear();
}

void Floor::init()
{
	m_points = NULL;
	m_uvs = NULL;
	buildFloor(Vector2(1.01f, 1.0f), Vector3(50.0f, 0.0f, 50.0f), 100, 100);
	
	m_ambient = new GLfloat[4];
	m_ambient[0] = 0.0f;
	m_ambient[1] = 0.7f;
	m_ambient[2] = 0.0f;
	m_ambient[3] = 1.0f;
	
	m_diffuse = m_ambient;
	
	m_specular = new GLfloat[4];
	m_specular[0] = 1.0f;
	m_specular[1] = 1.0f;
	m_specular[2] = 1.0f;
	m_specular[3] = 1.0f;
	
	m_shininess = new GLfloat;
	*m_shininess = 10;
	
	m_normal.y = 1.0f;
	
	m_texture = loadTexture("textures/ground.jpg");
}

void Floor::update(const float &deltaT)
{
	
}

void Floor::draw()
{
	if (!m_texture)
	{
		if (m_ambient)
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
		if (m_diffuse)
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
		if (m_specular)
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
		if (m_shininess)
			glMaterialfv(GL_FRONT, GL_SHININESS, m_shininess);
		glColor3f(0.0f, 0.7f, 0.0f);
	}
	else
	{
		if (m_ambient)
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_specular);
		if (m_diffuse)
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_specular);
		if (m_specular)
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
		if (m_shininess)
			glMaterialfv(GL_FRONT, GL_SHININESS, m_shininess);
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	if (Ass2::drawTextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	// Draw the plane:
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < indices.size(); ++i)
	{
		glTexCoord2fv(m_uvs[indices[i]].getV());
		glNormal3fv(m_normal.getV());
		glVertex3fv(m_points[indices[i]].getV());
	}
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	// Handle normals drawing:
	if (!Ass2::drawNormals)
		return;
	
	for (unsigned int i = 0; i < indices.size(); ++i)
	{
		Vector3 j = m_points[indices[i]] + Vector3(0.0f, 0.5f, 0.0f);
		kg::drawNormal(m_points[indices[i]], j);
	}
}

void Floor::clear()
{
	if (m_points)
		delete [] m_points;
	if (m_uvs)
		delete [] m_uvs;
}

void Floor::buildFloor(const Vector2 &scale, const Vector3 &pos,
		const int &rows, const int &columns)
{
	clear();
	indices.clear();
	
	m_points = new Vector3[rows * columns];
	m_uvs = new Vector2[rows * columns];
	
	int id;
	float s;
	
	// Build a grid of vertex m_points:
	for(int i = 0; i < rows; ++i)
	{
		s = (float)i/(float)rows;
		
		for(int j = 0; j < columns; ++j)
		{
			Vector3 coords((scale.x * (float)j) - pos.x, pos.y,
		    	(scale.y * (float)i) - pos.z);
			
			id = j + (i * rows);
		    m_points[id] = coords;
		 	m_uvs[id] = Vector2((float)j/(float)columns, s);
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

