#ifndef car_h
#define car_h

#include "object.h"

class Car : public Object
{
public:
    virtual void init();
	virtual void draw();
	virtual void update(const float &deltaT);
	
	Vector3 &getPos() { return m_pos; }
	Vector3 &getVel() { return m_vel; }

	float m_rockSpeed, rotY, rotZ;
	
	bool isCar;

private:
	float m_t;
};

#endif /* car_h */
