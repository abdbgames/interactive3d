#include "Mesh.h"
#include "PlatformInclude.h"
#include "Engine.h"
#include "Misc.h"

namespace kg
{
	Mesh::Mesh(const unsigned &uvs_size, const unsigned &normals_size,
		const unsigned &verts_size, const unsigned &indices_size,
		Vector2 **uvs, Vector3 **normals, Vector3 **verts,
		Index **indices, const std::string &name,
		const KG_MESH_MODE &renderType)
		: m_uvs_t(uvs_size), m_normals_t(normals_size), m_verts_t(verts_size),
		m_indices_t(indices_size), m_uvs(uvs), m_normals(normals),
		m_verts(verts), m_indices(indices), m_renderType(renderType)
	{
		m_name = name;
	}

	Mesh::~Mesh()
	{
		if (m_uvs)
		{
			for (unsigned i = 0; i < m_uvs_t; ++i)
				if (m_uvs[i])
					delete m_uvs[i];

			delete [] m_uvs;
		}

		if (m_normals)
		{
			for (unsigned i = 0; i < m_normals_t; ++i)
				if (m_normals[i])
					delete m_normals[i];

			delete [] m_normals;
		}

		if (m_verts)
		{
			for (unsigned i = 0; i < m_verts_t; ++i)
				if (m_verts[i])
					delete m_verts[i];

			delete [] m_verts;
		}

		if (m_indices)
		{
			for (unsigned i = 0; i < m_indices_t; ++i)
				if (m_indices[i])
					delete m_indices[i];

			delete [] m_indices;
		}
	}

	void Mesh::render()
	{
		// If there are no indices to draw, save some work:
		if (!m_indices) return;

		switch (m_renderType)
		{
		case KG_TRIS:
			glBegin(GL_TRIANGLES);
			break;
		case KG_TRI_STRIP:
			glBegin(GL_TRIANGLE_STRIP);
			break;
		case KG_TRI_FAN:
			glBegin(GL_TRIANGLE_FAN);
			break;
		case KG_QUADS:
			glBegin(GL_QUADS);
			break;
		case KG_QUAD_STRIP:
			glBegin(GL_QUAD_STRIP);
			break;
		default:
			printf("Unsupported render type!\n");
			return;
		}

		for (unsigned i = 0; i < m_indices_t; ++i)
		{
			glTexCoord2fv(m_uvs[m_indices[i]->uv]->getV());
			glNormal3fv(m_normals[m_indices[i]->n]->getV());
			glVertex3fv(m_verts[m_indices[i]->v]->getV());
		}

		glEnd();
	}

	void Mesh::renderDebugLines()
	{
		if (Engine::getDrawAxisEnabled())
			drawAxis(0.65f);

		if (Engine::getDrawNormalsEnabled())
		{
			glDisable(GL_LIGHTING);
			glBegin(GL_LINES);

			for (unsigned i = 0; i < m_indices_t; ++i)
			{
				Vector3 to = *m_normals[m_indices[i]->n];
				to.normalise();
				to = (to * 0.44f) + *m_verts[m_indices[i]->v];
				glVertex3fv(m_verts[m_indices[i]->v]->getV());
				glVertex3fv(to.getV());
			}

			glEnd();

			if (Engine::getLightState() != KG_UNLIT)
				glEnable(GL_LIGHTING);
		}
	}

	Mesh *Mesh::constructPlane(const unsigned &rows, const unsigned &columns)
	{
		Mesh *r = new Mesh();

		r->m_uvs_t = r->m_verts_t = rows * columns;
		r->m_indices_t = 0;
		r->m_normals_t = 1;

		for (int i = 0; i < rows - 1; ++i)
		{
			if (i != 0) ++r->m_indices_t;
			for (int j = 0; j < columns; ++j)
				r->m_indices_t += 2;
			if (i != rows - 2) ++r->m_indices_t;
		}

		++r->m_indices_t;

		r->m_uvs = new Vector2*[r->m_uvs_t];
		r->m_verts = new Vector3*[r->m_verts_t];
		r->m_normals = new Vector3*[r->m_normals_t];
		r->m_indices = new Index*[r->m_indices_t];
		r->m_normals[0] = new Vector3(0.0f, 1.0f, 0.0f);
		r->m_renderType = KG_TRI_STRIP;

		Vector2 scale(1.0f / (float)columns, 1.0f / (float)rows);

		unsigned id;
		float s;

		// Build a grid of vertex m_points:
		for (int i = 0; i < rows; ++i)
		{
			s = (float)i / (float)rows;

			for (int j = 0; j < columns; ++j)
			{
				id = j + (i * rows);
				r->m_verts[id] = new Vector3((scale.x * (float)j), 0.0f,
					(scale.y * (float)i));
				r->m_uvs[id] = new Vector2((float)j / (float)columns, s);
			}
		}

		unsigned back = 0;

		// Build an index list to access those vertcies in an order to make a
		// valid triangle strip:
		for (int i = 0; i < rows - 1; ++i)
		{
			if (i != 0)
			{
				id = i * rows;
				r->m_indices[back++] = new Index(id, 0, id);
			}

			for (int j = 0; j < columns; ++j)
			{
				id = i * columns + j;
				r->m_indices[back++] = new Index(id, 0, id);
				id = (i + 1) * columns + j;
				r->m_indices[back++] = new Index(id, 0, id);
			}

			if (i != rows - 2)
			{
				id = i * rows;
				r->m_indices[back++] = new Index(id, 0, id);
			}
		}

		return r;
	}

	Mesh *Mesh::constructCube()
	{
		Mesh *r = new Mesh;

		r->m_uvs_t = 4;
		r->m_verts_t = 8;
		r->m_indices_t = 36;
		r->m_normals_t = 6;
		r->m_renderType = KG_TRIS;

		r->m_uvs = new Vector2*[r->m_uvs_t];
		r->m_uvs[0] = new Vector2(0.0f, 0.0f);
		r->m_uvs[1] = new Vector2(0.0f, 1.0f);
		r->m_uvs[2] = new Vector2(1.0f, 0.0f);
		r->m_uvs[3] = new Vector2(1.0f, 1.0f);

		r->m_normals = new Vector3*[r->m_normals_t];
		r->m_normals[0] = new Vector3(1.0f, 0.0f, 0.0f);
		r->m_normals[1] = new Vector3(-1.0f, 0.0f, 0.0f);
		r->m_normals[2] = new Vector3(0.0f, 1.0f, 0.0f);
		r->m_normals[3] = new Vector3(0.0f, -1.0f, 0.0f);
		r->m_normals[4] = new Vector3(0.0f, 0.0f, 1.0f);
		r->m_normals[5] = new Vector3(0.0f, 0.0f, -1.0f);

		r->m_verts = new Vector3*[r->m_verts_t];
		r->m_verts[0] = new Vector3(-0.5f, -0.5f, -0.5f);
		r->m_verts[1] = new Vector3(0.5f, -0.5f, -0.5f);
		r->m_verts[2] = new Vector3(-0.5f, -0.5f, 0.5f);
		r->m_verts[3] = new Vector3(0.5f, -0.5f, 0.5f);
		r->m_verts[4] = new Vector3(-0.5f, 0.5f, -0.5f);
		r->m_verts[5] = new Vector3(0.5f, 0.5f, -0.5f);
		r->m_verts[6] = new Vector3(-0.5f, 0.5f, 0.5f);
		r->m_verts[7] = new Vector3(0.5f, 0.5f, 0.5f);

		r->m_indices = new Index*[r->m_indices_t];
		r->m_indices[0] = new Index(0, 3, 0);
		r->m_indices[1] = new Index(2, 3, 1);
		r->m_indices[2] = new Index(1, 3, 2);
		r->m_indices[3] = new Index(1, 3, 2);
		r->m_indices[4] = new Index(3, 3, 3);
		r->m_indices[5] = new Index(2, 3, 1);
		r->m_indices[6] = new Index(0, 1, 0);
		r->m_indices[7] = new Index(4, 1, 1);
		r->m_indices[8] = new Index(2, 1, 2);
		r->m_indices[9] = new Index(2, 1, 2);
		r->m_indices[10] = new Index(6, 1, 3);
		r->m_indices[11] = new Index(4, 1, 1);
		r->m_indices[12] = new Index(1, 0, 1);
		r->m_indices[13] = new Index(5, 0, 0);
		r->m_indices[14] = new Index(3, 0, 1);
		r->m_indices[15] = new Index(3, 0, 2);
		r->m_indices[16] = new Index(7, 0, 2);
		r->m_indices[17] = new Index(5, 0, 3);
		r->m_indices[18] = new Index(4, 2, 0);
		r->m_indices[19] = new Index(6, 2, 1);
		r->m_indices[20] = new Index(5, 2, 2);
		r->m_indices[21] = new Index(5, 2, 2);
		r->m_indices[22] = new Index(7, 2, 3);
		r->m_indices[23] = new Index(6, 2, 1);
		r->m_indices[24] = new Index(0, 5, 0);
		r->m_indices[25] = new Index(4, 5, 1);
		r->m_indices[26] = new Index(1, 5, 2);
		r->m_indices[27] = new Index(1, 5, 2);
		r->m_indices[28] = new Index(5, 5, 3);
		r->m_indices[29] = new Index(4, 5, 1);
		r->m_indices[30] = new Index(2, 4, 0);
		r->m_indices[31] = new Index(6, 4, 1);
		r->m_indices[32] = new Index(3, 4, 2);
		r->m_indices[33] = new Index(3, 4, 2);
		r->m_indices[34] = new Index(7, 4, 3);
		r->m_indices[35] = new Index(6, 4, 1);

		return r;
	}

	Mesh *Mesh::constructCircle(const unsigned &slices)
	{
		Mesh *r = new Mesh;

		r->m_indices_t = slices + 1;
		r->m_uvs_t = slices + 1;
		r->m_verts_t = slices + 1;

		r->m_uvs = new Vector2*[r->m_uvs_t];
		r->m_verts = new Vector3*[r->m_verts_t];
		r->m_normals = new Vector3*[r->m_normals_t];
		r->m_indices = new Index*[r->m_indices_t];
		r->m_normals[0] = new Vector3(0.0f, 1.0f, 0.0f);
		r->m_renderType = KG_TRI_FAN;

		r->m_verts[0] = new Vector3();
		r->m_uvs[0] = new Vector2(0.5f, 0.5f);
		r->m_indices[0] = new Index(0, 0, 0);

		float t;

		for (unsigned i = 1; i <= slices; ++i)
		{
			t = ((float)i / (float)slices) * 2.0f * KG_PI;
			r->m_verts[i] = new Vector3(cos(t), 0.0f, sin(t));
			r->m_uvs[i] = new Vector2((r->m_verts[i]->x * 0.5f) + 0.5f,
				(r->m_verts[i]->z * 0.5f) + 0.5f);
			r->m_indices[i] = new Index(i, 0, i);
		}

		return r;
	}

	Mesh *Mesh::constructCylinder(const unsigned &stacks,
		const unsigned &slices)
	{
		Mesh *r = new Mesh;



		return r;
	}

	Mesh *Mesh::constructSphere(const unsigned &stacks,
		const unsigned &slices)
	{
		Mesh *r = new Mesh;
		
		
		
		return r;
	}

	std::map<std::string, Mesh*> MeshTable::m_list;

	void MeshTable::cleanup()
	{
		for (std::map<std::string, Mesh*>::iterator i = m_list.begin();
			i != m_list.end(); ++i)
			delete i->second;
	}

	void MeshTable::pushMesh(const std::string &name, Mesh *m)
	{
		std::map<std::string, Mesh*>::iterator i = m_list.find(name);
		
		if (i != m_list.end())
		{
			delete i->second;
			i->second = m;
		}
		else
			m_list.insert(std::pair<std::string, Mesh*>(name, m));

		m->setName(name);
	}
	
	bool MeshTable::canFind(const std::string &name)
	{
		return (m_list.find(name) == m_list.end());
	}
}
