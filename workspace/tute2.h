#ifndef tute2_h
#define tute2_h

#include "tute.h"
#include "vectors.h"

class Tute2 : public Tute
{
public:
	Tute2(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	virtual void end();

private:
	void drawAxis(const float &x, const float &y, const float &z, const float &size);
	void drawFormula(const float &xMin, const float &xMax, const int &steps);
	void drawTangent(const float &x);
	void drawCircleCartesian(const Vector3 &v, const float &r, const int &steps);

	int m_steps;
	float m_r;
	Vector3 m_pos;
	
	float getLinearY(const float &x);
	float getQuadraticY(const float &x);
};

#endif /* tute2_h */
