#ifndef log_h
#define log_h

#include "object.h"

struct LogCap : public kg::Object
{
	LogCap();
};

struct Log : public kg::Object
{
	Log(const bool &dir);

	virtual void start();
	virtual void update();

	float *getBounds() { return &m_left; }
	
protected:
	float m_left, m_right, m_front, m_back, m_top, m_bot;

	bool m_dir;

	LogCap *m_l, *m_r;
};

#endif /* log_h */
