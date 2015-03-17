#ifndef tute2_h
#define tute2_h

#include "tute.h"

class Tute2 : public Tute
{
public:
	Tute2(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	virtual void end();

private:
	void drawAxis(float x, float y, float z, float size);
	void drawFormula(float xMin, float xMax, int steps);
	void drawTangent(float x);
	void drawCircleCartesian(float r, int steps);

	int m_steps;
	
	float getLinearY(float x);
	float getQuadraticY(float x);
};

#endif /* tute2_h */
