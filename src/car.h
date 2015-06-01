#ifndef car_h
#define car_h

#include "object.h"

struct CarWheel : public kg::Object
{
	CarWheel();
};

struct CarTop : public kg::Object
{
	CarTop();
};

struct Car : public kg::Object
{
	Car(const bool &dir);

	virtual void start();
	virtual void update();

	float m_radius;

protected:
	bool m_dir;

	CarTop *m_ct;

	CarWheel *m_fl, *m_fr, *m_bl, *m_br;
};

#endif /* car_h */
