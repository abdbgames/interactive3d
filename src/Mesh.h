#ifndef mesh_h
#define mesh_h

#include <map>
#include <string>

#include "ObjectProperties.h"
#include "Vectors.h"
#include "KGConstants.h"

namespace kg
{
	struct Index
	{
		Index(int _v, int _n, int _uv) : v(_v), n(_n), uv(_uv) {}
		unsigned v, n, uv;
	};

	struct Mesh : public BaseProperty
	{
		Mesh() : m_uvs_t(0), m_normals_t(0), m_verts_t(0), m_indices_t(0),
			m_name(NULL), m_uvs(NULL), m_normals(NULL), m_verts(NULL),
			m_indices(NULL), m_renderType(KG_TRIS) {}
		Mesh(const unsigned &uvs_size, const unsigned &normals_size,
			const unsigned &verts_size, const unsigned &indices_size,
			Vector2 **uvs, Vector3 **normals, Vector3 **verts,
			Index **indices, const char *name,
			const KG_MESH_MODE &renderType);

		~Mesh();

		void render();

		unsigned m_uvs_t, m_normals_t, m_verts_t, m_indices_t;

		char *m_name;

		Vector2 **m_uvs;

		Vector3 **m_normals, **m_verts;

		Index **m_indices;

		KG_MESH_MODE m_renderType;

		static Mesh *constructPlane(const unsigned &rows,
			const unsigned &columns);
		static Mesh *constructCube();
		static Mesh *constructCircle(const unsigned &slices);

	private:
		void renderDebugLines();
	};

	struct MeshTable
	{
		static void cleanup();
		static void pushMesh(const std::string &name, Mesh *m);

		static bool canFind(const std::string &name);

	private:
		static std::map<std::string, Mesh*> m_list;
	};
}

#endif /* mesh_h */
