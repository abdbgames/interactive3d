#ifndef object_h
#define object_h

#include "vectors.h"

class Object
{
public:
	virtual void init() {}
	virtual void draw() {}
	virtual void update(const float &deltaT) {}
	virtual void end() {}
	
	Vector3 *getPos() { return &m_pos; }
	
	void setDir(const float &dir);
	
protected:
	Vector3 m_pos, m_vel, m_dir;
};

#endif /* object_h */

