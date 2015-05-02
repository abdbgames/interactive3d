#ifndef meshes_h
#define meshes_h

#include "platformInclude.h"
#include "vectors.h"
#include <vector>

struct Index
{
	Index(int _v, int _n, int _uv) : v(_v), n(_n), uv(_uv) {}
	int v, n, uv;
};

struct CarMesh
{
	static CarMesh *get();

	void draw();
protected:
	CarMesh();
	~CarMesh();

	GLfloat *m_ambient, *m_diffuse, *m_specular, m_shininess;
	
	int indieces;
	
	float m_size;
	
	Index **m_indices;
	
	Vector2 **m_uvs;
	
	Vector3 **m_verts, **m_normals;
	
	static CarMesh *m_instance;
};

struct LogMesh
{
	static LogMesh *get();

	void draw();
protected:
	LogMesh();
	~LogMesh();
	
	GLfloat *m_ambient, *m_diffuse, *m_specular, m_shininess;
	
	int m_edges, m_stacks, m_texture;
	
	Vector3 **m_verts;

	Vector2 **m_normals, **m_uvs;
	
	std::vector<Index> m_indices;
	
	static LogMesh *m_instance;
};

#endif /* meshes_h */

