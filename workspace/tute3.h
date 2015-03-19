#ifndef tute3_h
#define tute3_h

#include "tute.h"

class Tute3 : public Tute
{
public:
	Tute3(const char *name) : Tute(name) {}

	virtual void init();
	virtual void draw();
	virtual void update();
	virtual void end();
};

#endif /* tute3_h */
