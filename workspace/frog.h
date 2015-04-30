#ifndef frog_h
#define frog_h

#include "object.h"
#include <vector>

class Frog : public Object
{
public:
    virtual void init();
	virtual void draw();
	virtual void update(const float &deltaT);
	
	bool m_inAir;
	
	void remakeSphere(const int &detail, const float &radius);
	
private:
	void drawParabola();

	std::vector<Vector3> points;
	
	Vector3 m_initPos, m_initVel;
	Vector2 m_vel2, m_angle;
	
	int m_pSteps, m_cDetail;
	
	float m_radius, m_rotSpeed, m_speed;
};

#endif /* frog_h */

