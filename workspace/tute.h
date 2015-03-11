#ifndef tute_h
#define tute_h

#include "keyboard.h"

class Tute
{
public:
	Tute(const char *name)
	{
		m_name = _strdup(name);
	}

	~Tute()
	{
		free(m_name);
	}

	virtual void init() {}
	virtual void draw() {}
	virtual void update() {}
	virtual void fixedUpdate() {}
	virtual void end() {}
	
	char *getName() { return m_name; }

protected:
	char *m_name;
};

#endif /* tute_h */
