#ifndef object_h
#define object_h

#include "vectors.h"
#include "platformInclude.h"

class Object
{
public:
	Object() : m_ambient(NULL), m_diffuse(NULL), m_specular(NULL), 
		m_shininess(NULL) {}
	~Object();
	
	virtual void init() {}
	virtual void draw() {}
	virtual void update(const float &deltaT) {}
	virtual void end() {}
	
	Vector3 *getPos() { return &m_pos; }
	
	void setDir(const float &dir);
	
protected:
	Vector3 m_pos, m_vel, m_dir;
	
	GLfloat *m_ambient, *m_diffuse, *m_specular, *m_shininess;
};

#endif /* object_h */

