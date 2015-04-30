#ifndef ass2_h
#define ass2_h

#include "tute.h"
#include "vectors.h"
#include "frog.h"
#include "camera.h"
#include "floor.h"
#include "car.h"

class Ass2 : public Tute
{
public:
	Ass2(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	
	static KG_DRAW_MODE getDrawState() { return drawMode; }
	static KG_LIGHT_MODE getLightState() { return lightMode; }
	
	static bool drawAxis, drawNormals, drawTextures;
	
	static bool isSmoothShading() { return smoothShading; }
	
	static void setDrawState(const KG_DRAW_MODE &d);
	static void setLightState(const KG_LIGHT_MODE &l);
	static void setSmoothShading(const bool &ss);
	static void cycleDrawState();
	static void cycleLightState();
	static void toggleSmoothShading();
	static void grabSize(int w, int h);

private:
	void updateTime();

	int m_dynObjects;

	bool m_debug;
	
	static bool smoothShading;
	
	static int m_width, m_height;
	
	static KG_DRAW_MODE drawMode;
	static KG_LIGHT_MODE lightMode;
	
	float m_t, m_sT, m_dT;
	
	static float m_aspect;
	
	Frog m_frog;
	Camera m_camera;
	Floor m_floor;
	
	std::vector<Car> m_dynObjList;
};

#endif /* ass1_h */

