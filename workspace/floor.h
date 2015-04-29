#ifndef floor_h
#define floor_h

#include "object.h"
#include <vector>

class Floor : public Object
{
public:
	~Floor();

    virtual void init();
	virtual void draw();
	virtual void update(const float &deltaT);
	
	void buildFloor(const Vector2 &scale, const Vector3 &pos,
		const int &rows, const int &columns);
	
private:
	Vector3 *points;
	
	std::vector<int> indices;
};

#endif /* floor_h */

