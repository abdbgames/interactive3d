#ifndef ass2_h
#define ass2_h

#include "tute.h"
#include "vectors.h"
#include "frog.h"
#include "camera.h"
#include "floor.h"

class Ass2 : public Tute
{
public:
	Ass2(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	
	static void grabSize(int w, int h);

private:
	void updateTime();
	void drawAxis(const Vector3 &pos, const float &size);

	bool m_debug;

	float m_t, m_sT, m_dT;
	
	static float m_aspect;
	
	static int m_width, m_height;
	
	Frog m_frog;
	Camera m_camera;
	Floor m_floor;
};

#endif /* ass1_h */
