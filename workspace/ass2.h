#ifndef ass2_h
#define ass2_h

#include "tute.h"
#include "vectors.h"
#include "frog.h"

class Ass2 : public Tute
{
public:
	Ass2(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();

private:
	void updateTime();
	void drawAxis(const Vector3 &pos, const float &size);

	bool m_debug;

	float m_t, m_sT, m_dT;
	
	Frog m_frog;
};

#endif /* ass1_h */
