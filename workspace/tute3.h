#ifndef tute3_h
#define tute3_h

#include "tute.h"
#include "vectors.h"

class Tute3 : public Tute
{
public:
	Tute3(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	virtual void end();

	void updateTime();
	void drawAxis(const float &x, const float &y, const float &z, const float &size);
	void drawCircleCartesian(const Vector3 &pos, const float &radius, const int &steps);
	void drawCirecleParametric(const Vector3 &pos, const float &radius, const int &steps);
	void drawLine(Vector3 &pos, const Vector3 &to, const bool &normalise);

	float t, dt;
};

#endif /* tute3_h */
