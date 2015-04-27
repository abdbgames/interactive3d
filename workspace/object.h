#ifndef object_h
#define object_h

#include "vectors.h"

class Object
{
public:
	virtual void init() {}
	virtual void draw() {}
	virtual void update() {}
	virtual void end() {}
	
	void setDir(const float &dir);
	
protected:
	Vector3 m_pos, m_vel, m_dir;
};

#endif /* object_h */

