#include "stdafx.h"
#include "mouse.h"

namespace kg
{
	std::vector<int> mouseControl::m_pressed,
		mouseControl::m_press,
		mouseControl::m_released;
		
	int mouseControl::m_x = 0,
		mouseControl::m_y = 0,
		mouseControl::m_xL = 0,
		mouseControl::m_yL = 0,
		mouseControl::m_xD = 0,
		mouseControl::m_yD = 0;
		
	bool mouseControl::m_lock = true;
		
	void mouseControl::mouseMoveCallback(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	
	void mouseControl::mousePressCallback(int button, int state, int x, int y)
	{
		std::vector<int>::iterator i = findElement(m_pressed, button);
	
		switch (state)
		{
		case GLUT_DOWN:
			// Check if the button is in the pressed list:
			if (i == m_pressed.end())
			{
				// The button was pressed for the first time:
				m_pressed.push_back(button);
				m_press.push_back(button);
			}
			break;
		case GLUT_UP:
			// Check if the button is in the pressed list, and remove it:
			if (i != m_pressed.end())
				m_pressed.erase(i);
				
			m_released.push_back(button);
			break;
		default:
			break;
		}
	}
	
	void mouseControl::setMousePos(int x, int y)
	{
		glutWarpPointer(x, y);
	}
	
	void mouseControl::lockMouse(int x, int y)
	{
		if (!m_lock)
		{
			m_lock = true;
			m_xL = x;
			m_yL = y;
		}
	}
	
	void mouseControl::postUpdate()
	{
		// Empty the press and release lists:
		m_press.clear();
		m_released.clear();
		
		// If we need to lock the mouse then do it:
		if (m_lock)
		{
			// Work out difference in mouse positioning:
			m_xD = m_xL - m_x;
			m_yD = m_yL - m_y;
			setMousePos(m_xL, m_yL);
		}
		else
		{
			// Nothing moved:
			m_xD = 0;
			m_yD = 0;
		}
	}
	
	bool mouseControl::poll(const int &b, const KG_PRESS_TYPE &p)
	{
		switch (p)
		{
		case KG_DOWN:
			return (findElement(m_press, b) != m_press.end());
		case KG_PRESSED:
			return (findElement(m_pressed, b) != m_pressed.end());
		case KG_UP:
			return (findElement(m_released, b) != m_released.end());
		}
		
		return false;
	}
	
	bool mouseControl::pollAny(const KG_PRESS_TYPE &p)
	{
		switch (p)
		{
		case KG_DOWN:
			return (m_press.size() != 0);
		case KG_PRESSED:
			return (m_pressed.size() != 0);
		case KG_UP:
			return (m_released.size() != 0);
		}
		
		return false;
	}
	
	std::vector<int>::iterator mouseControl::findElement(std::vector<int> &v,
			const int &b)
	{
		std::vector<int>::iterator i;

		for (i = v.begin(); i < v.end(); ++i)
			if (*i == b)
				return i;

		return i;
	}
}

