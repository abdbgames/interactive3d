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
	
	void remakeSphere(const int &detail, const float &radius);
	
private:
	std::vector<Vector3> points;
};

#endif /* frog_h */

