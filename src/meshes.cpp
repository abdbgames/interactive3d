#include "stdafx.h"
#include "meshes.h"

CarMesh *CarMesh::m_instance = NULL;

CarMesh *CarMesh::get()
{
	m_instance = (m_instance) ? m_instance : new CarMesh();
	return m_instance;
}

CarMesh::CarMesh()
{
	//gluQuad = gluNewQuadric();
	m_ambient = new GLfloat[4];
	m_ambient[0] = 0.83f;
	m_ambient[1] = 0.0f;
	m_ambient[2] = 0.12f;
	m_ambient[3] = 1.0f;
	
	m_diffuse = m_ambient;
	
	m_specular = new GLfloat[4];
	m_specular[0] = 1.0f;
	m_specular[1] = 1.0f;
	m_specular[2] = 1.0f;
	m_specular[3] = 1.0f;
	
	m_shininess = 50;
	m_size = 0.4f;
	
	m_uvs = new Vector2*[4];
	m_uvs[0] = new Vector2(0.0f, 0.0f);
	m_uvs[1] = new Vector2(0.0f, 1.0f);
	m_uvs[2] = new Vector2(1.0f, 0.0f);
	m_uvs[3] = new Vector2(1.0f, 1.0f);
	
	m_normals = new Vector3*[6];
	m_normals[0] = new Vector3(1.0f, 0.0f, 0.0f);
	m_normals[1] = new Vector3(-1.0f, 0.0f, 0.0f);
	m_normals[2] = new Vector3(0.0f, 1.0f, 0.0f);
	m_normals[3] = new Vector3(0.0f, -1.0f, 0.0f);
	m_normals[4] = new Vector3(0.0f, 0.0f, 1.0f);
	m_normals[5] = new Vector3(0.0f, 0.0f, -1.0f);
	
	m_verts = new Vector3*[8];
	m_verts[0] = new Vector3(-m_size, -m_size, -m_size);
	m_verts[1] = new Vector3(m_size, -m_size, -m_size);
	m_verts[2] = new Vector3(-m_size, -m_size, m_size);
	m_verts[3] = new Vector3(m_size, -m_size, m_size);
	m_verts[4] = new Vector3(-m_size, m_size, -m_size);
	m_verts[5] = new Vector3(m_size, m_size, -m_size);
	m_verts[6] = new Vector3(-m_size, m_size, m_size);
	m_verts[7] = new Vector3(m_size, m_size, m_size);
	
	m_indices = new Index*[36];
	m_indices[0] = new Index(0, 3, 0);
	m_indices[1] = new Index(2, 3, 1);
	m_indices[2] = new Index(1, 3, 2);
	m_indices[3] = new Index(1, 3, 2);
	m_indices[4] = new Index(3, 3, 3);
	m_indices[5] = new Index(2, 3, 1);
	m_indices[6] = new Index(0, 1, 0);
	m_indices[7] = new Index(4, 1, 1);
	m_indices[8] = new Index(2, 1, 2);
	m_indices[9] = new Index(2, 1, 2);
	m_indices[10] = new Index(6, 1, 3);
	m_indices[11] = new Index(4, 1, 1);
	m_indices[12] = new Index(1, 0, 1);
	m_indices[13] = new Index(5, 0, 0);
	m_indices[14] = new Index(3, 0, 1);
	m_indices[15] = new Index(3, 0, 2);
	m_indices[16] = new Index(7, 0, 2);
	m_indices[17] = new Index(5, 0, 3);
	m_indices[18] = new Index(4, 2, 0);
	m_indices[19] = new Index(6, 2, 1);
	m_indices[20] = new Index(5, 2, 2);
	m_indices[21] = new Index(5, 2, 2);
	m_indices[22] = new Index(7, 2, 3);
	m_indices[23] = new Index(6, 2, 1);
	m_indices[24] = new Index(0, 5, 0);
	m_indices[25] = new Index(4, 5, 1);
	m_indices[26] = new Index(1, 5, 2);
	m_indices[27] = new Index(1, 5, 2);
	m_indices[28] = new Index(5, 5, 3);
	m_indices[29] = new Index(4, 5, 1);
	m_indices[30] = new Index(2, 4, 0);
	m_indices[31] = new Index(6, 4, 1);
	m_indices[32] = new Index(3, 4, 2);
	m_indices[33] = new Index(3, 4, 2);
	m_indices[34] = new Index(7, 4, 3);
	m_indices[35] = new Index(6, 4, 1);
}
	
CarMesh::~CarMesh()
{
	//gluDeleteQuadric(gluQuad);
	delete [] m_ambient;
	delete [] m_diffuse;
	delete [] m_specular;
	
	for (int i = 0; i < 36; ++i)
	{
		delete m_indices[i];
		if (i < 8)
			delete m_verts[i];
		else continue;
		if (i < 6)
			delete m_normals;
		else continue;
		if (i < 4)
			delete m_uvs;
	}
	
	delete [] m_verts;
	delete [] m_normals;
	delete [] m_uvs;
	delete [] m_indices;
}

void CarMesh::draw()
{
	// Material:
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
	glColor3f(0.83f, 0.0f, 0.12f);
	
	// positioning:
	glPushMatrix();
	glTranslatef(0.0f, m_size, 0.0f);
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; ++i)
	{
		glTexCoord2fv(m_uvs[m_indices[i]->uv]->getV());
		glNormal3fv(m_normals[m_indices[i]->n]->getV());
		glVertex3fv(m_verts[m_indices[i]->v]->getV());
	}
	glEnd();
	glPopMatrix();
}

LogMesh *LogMesh::m_instance = NULL;

LogMesh *LogMesh::get()
{
	m_instance = (m_instance) ? m_instance : new LogMesh();
	return m_instance;
}

LogMesh::LogMesh()
{
	gluQuad = gluNewQuadric();
	
	m_ambient = new GLfloat[4];
	m_ambient[0] = 0.2f;
	m_ambient[1] = 0.1f;
	m_ambient[2] = 0.0f;
	m_ambient[3] = 1.0f;
	
	m_diffuse = m_ambient;
	
	m_specular = new GLfloat[4];
	m_specular[0] = 1.0f;
	m_specular[1] = 1.0f;
	m_specular[2] = 1.0f;
	m_specular[3] = 1.0f;
	
	m_shininess = 12;
	
	m_edges = 20;
	
	m_points = new Vector3*[m_edges+1];
	
	float t;
	
	for (int i = 0; i <= m_edges; ++i)
	{
		t = ((float)i / (float)m_edges) * 2.0f * KG_PI;
		m_points[i] = new Vector3(cos(t),sin(t), 0.0f);
	}
	
	m_texture = loadTexture("textures/wood.jpg");
	
	if (!m_texture)
		printf("textures/wood.jpg failed to load!\n");
}
	
LogMesh::~LogMesh()
{
	gluDeleteQuadric(gluQuad);
	delete [] m_ambient;
	delete [] m_diffuse;
	delete [] m_specular;
	
	for (int i = 0; i <= m_edges; ++i)
		delete m_points[i];
	
	delete [] m_points;
}

void LogMesh::draw()
{
	// Material:
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	// positioning:
	glPushMatrix();
	glTranslatef(0.0f, 0.13f, 0.0f);
	glScalef(0.2f, 0.2f, 1.0f);
	
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	
	// TODO: Vertex buffer for log:
	gluCylinder(gluQuad, 1.0f, 1.0f, 2.0f, 20, 30);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
	glColor3f(0.2f, 0.1f, 0.0f);
	
	// Draw cylinder caps:
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i <= m_edges; ++i)
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(m_points[i]->getV());
	}
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 2.0f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i <= m_edges; ++i)
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(m_points[i]->getV());
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

