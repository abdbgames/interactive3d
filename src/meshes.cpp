#include "meshes.h"
#include "ass2.h"

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
	
	m_edges = 25;
	m_stacks = 10;
	
	m_verts = new Vector3*[m_edges * m_stacks];
	m_uvs = new Vector2*[(m_edges + 1) * m_stacks];
	m_normals = new Vector2*[m_edges + 1];
	
	float t, width = 2.0f, hWidth = width * 0.5f;
	int id, idb;
	
	for (int i = 0; i < m_edges; ++i)
	{
		// Work out the normals, they also count as our circle values for when
		// we need them:
		if (i < m_edges)
		{
			t = ((float)i / (float)m_edges) * 2.0f * KG_PI;
			m_normals[i] = new Vector2(cos(t), sin(t));
		}

		idb = i * m_stacks;

		for (int j = 0; j < m_stacks; ++j)
		{
			// Each point will be the normal value with the z being added
			// as the current stack / width:
			id = j + idb;
			m_verts[id] = new Vector3(*m_normals[i]);
			m_verts[id]->z = (float)j * (width / (m_stacks - 1)) - hWidth;

			// Each uv will be the current edge / edges for y and current
			// stack / stacks for x:
			m_uvs[id] = new Vector2((float)j / (float)m_stacks,
				(float)i / (float)m_edges);

			if (i == m_edges - 1)
				m_uvs[m_stacks * m_edges + j] = new Vector2((float)j /
					(float)m_stacks, 1.0f);
		}
	}

	// Build an index list for a triangle strip with degenerate triangles:
	idb = 0;

	int uv;

	for (int i = 0; i < m_edges; ++i)
	{
		id = idb;
		uv = (i + 1) * m_stacks;
		idb = (i == m_edges - 1) ? 0 : uv;

		if (i != 0)
			m_indices.push_back(Index(id, i, uv));

		for (int j = 0; j < m_stacks; ++j)
		{
			m_indices.push_back(Index(id + j, i, id + j));
			m_indices.push_back(Index(idb + j, i, uv + j));
		}

		if (i != (m_edges - 1))
			m_indices.push_back(Index(idb + (m_stacks - 1), i,
				uv + (m_stacks - 1)));
	}
	
	m_texture = loadTexture("textures/wood.jpg");
}
	
LogMesh::~LogMesh()
{
	delete [] m_ambient;
	delete [] m_diffuse;
	delete [] m_specular;

	for (int i = 0; i < (m_edges + 1) * m_stacks; ++i)
	{
		if (i < m_edges * m_stacks)
			delete m_uvs[i];
		else continue;
		if (i < m_edges)
			delete m_normals[i];
		delete m_verts[i];
	}
	
	delete [] m_normals;
	delete[] m_verts;
	delete[] m_uvs;
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

	if (Ass2::drawTextures)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	else
		glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < m_indices.size(); ++i)
	{
		glTexCoord2fv(m_uvs[m_indices[i].uv]->getV());
		glNormal3f(m_normals[m_indices[i].n]->x, m_normals[m_indices[i].n]->y,
			0.0f);
		glVertex3fv(m_verts[m_indices[i].v]->getV());
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
	glColor3f(0.2f, 0.1f, 0.0f);
	
	// Draw cylinder caps:
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < m_edges; ++i)
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex2fv(m_normals[i]->getV());
	}
	glVertex2fv(m_normals[0]->getV());
	glEnd();
	glTranslatef(0.0f, 0.0f, 2.0f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < m_edges; ++i)
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex2fv(m_normals[i]->getV());
	}
	glVertex2fv(m_normals[0]->getV());
	glEnd();
	glPopMatrix();
}

