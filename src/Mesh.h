#ifndef mesh_h
#define mesh_h

#include "ObjectProperties.h"
#include "Vectors.h"

namespace kg
{
	struct Index
	{
		Index(int _v, int _n, int _uv) : v(_v), n(_n), uv(_uv) {}
		int v, n, uv;
	};

	struct BaseMesh
	{
		unsigned m_uvs_t, m_normals_t, m_verts_t, m_indicies_t;

		Vector2 **m_uvs;
		Vector3 **m_normals, **m_verts;
		Index **m_indicies;
	};

	struct CylinderMesh : public BaseMesh
	{

	};

	struct CubeMesh : BaseMesh
	{

	};

	struct SphereMesh : BaseMesh
	{

	};

	struct PlaneMesh : BaseMesh
	{

	};

	struct Mesh : public BaseProperty
	{
		
	};
}

#endif /* mesh_h */
