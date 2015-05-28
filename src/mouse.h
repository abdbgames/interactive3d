#ifndef mouse_h
#define mouse_h

#include <vector>

#include "kgConstants.h"

namespace kg
{
	struct mouseControl
	{
		static void mouseMoveCallback(int x, int y);
		static void mousePressCallback(int button, int state, int x, int y);
		static void setMousePos(int x, int y);
		static void lockMouse() { m_lock = true; }
		static void lockMouse(int x, int y);
		static void unlockMouse() { m_lock = false; }
		static void postUpdate();

		static bool poll(const int &b, const KG_PRESS_TYPE &p);
		static bool pollAny(const KG_PRESS_TYPE &p);

		static int *pollMouseMoved() { return &m_xD; }

		static int m_x, m_y;

	protected:
		static std::vector<int> m_pressed, m_press, m_released;

		static std::vector<int>::iterator findElement(std::vector<int> &v,
			const int &b);

		static int m_xL, m_yL, m_xD, m_yD;

		static bool m_lock;
	};
}

#endif /* mouse_h */
