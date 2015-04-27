#ifndef tute1_h
#define tute1_h

#include "tute.h"

class Tute1 : public Tute
{
public:
	Tute1(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	virtual void end();
};

#endif /* tute1_h */
