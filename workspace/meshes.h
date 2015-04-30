#ifndef meshes_h
#define meshes_h

#include "platformInclude.h"

struct CarMesh
{
	static CarMesh *get();

	void draw();
protected:
	CarMesh();
	~CarMesh();
	
	//GLUquadratic *gluQuad;
	
	static CarMesh *m_instance;
};

struct LogMesh
{
	static LogMesh *get();

	void draw();
protected:
	LogMesh();
	~LogMesh();
	
	GLUquadric *gluQuad;
	
	static LogMesh *m_instance;
};

#endif /* meshes_h */

