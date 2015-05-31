#ifndef log_h
#define log_h

#include "object.h"

struct LogCap : public kg::Object
{
	LogCap();
};

struct Log : public kg::Object
{
	Log();

	virtual void start();
	virtual void update();
	
	LogCap *m_l, *m_r;
};

#endif /* log_h */
