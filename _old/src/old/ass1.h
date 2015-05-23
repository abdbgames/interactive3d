#ifndef ass1_h
#define ass1_h

#include "tute.h"
#include "vectors.h"

class Ass1 : public Tute
{
public:
	Ass1(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();

private:
	void updateTime();
	void drawAxis(const Vector3 &pos, const float &size);
	void updateCircleCartesian();
	void updateCircleParametric();
	void drawCircle();
	void drawParabolaCartesian();
	void drawParabolaParametric();
	void drawLine(Vector3 pos, Vector3 to, const Vector3 &colour);

	std::vector<Vector2> m_circlePoints;

	Vector2 frogPos, frogVel, frogPosI, frogVelI;

	bool frogInAir, m_paraCart, m_circleCart, m_debug, m_drawNormals,
		m_drawTangents, m_analytical;

	float m_t, m_sT, m_dT, m_radius, m_dir, m_speed, m_keySpeed,
		m_dist, screenLeft, screenRight, screenDist;

	int m_paraSteps, m_circleSteps;
};

#endif /* ass1_h */
