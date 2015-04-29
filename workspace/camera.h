#ifndef camera_h
#define camera_h

#include "object.h"

class Camera : public Object
{
public:
    virtual void init();
	virtual void draw();
	virtual void update(const float &deltaT);
	
	void updateSize(float *a) { m_aspect = a; }
	void updateOrigin(Vector3 *o) { m_origin = o; }
	
	void remakeSphere(const int &detail, const float &radius);

protected:
	void updateBoom();

	Vector3 *m_origin;

	float m_speed, *m_aspect, m_dist, m_angle;
};

#endif /* camera_h */

