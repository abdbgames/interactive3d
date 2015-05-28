#include "keyboard.h"

namespace kg
{
	std::vector<KG_KEY_TYPE> keyboardControl::m_pressed,
		keyboardControl::m_press,
		keyboardControl::m_released;

	void keyboardControl::keyboardCallback(KG_KEY_TYPE key, int x, int y)
	{
		std::vector<KG_KEY_TYPE>::iterator i = findElement(m_pressed, key);

		// Check if the key is in the pressed list:
		if (i == m_pressed.end())
		{
			// The button was pressed for the first time:
			m_pressed.push_back(key);
			m_press.push_back(key);
		}
	}

	void keyboardControl::keyboardUpCallback(KG_KEY_TYPE key, int x, int y)
	{
		// Check if the button is in the pressed list, and remove it:
		std::vector<KG_KEY_TYPE>::iterator i = findElement(m_pressed, key);

		if (i != m_pressed.end())
		{
			m_pressed.erase(i);
			m_released.push_back(key);
		}
	}

	void keyboardControl::specialCallback(int key, int x, int y)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			keyboardCallback(KGKey_left, x, y);
			break;
		case GLUT_KEY_RIGHT:
			keyboardCallback(KGKey_right, x, y);
			break;
		case GLUT_KEY_UP:
			keyboardCallback(KGKey_up, x, y);
			break;
		case GLUT_KEY_DOWN:
			keyboardCallback(KGKey_down, x, y);
			break;
		default:
			break;
		}
	}

	void keyboardControl::specialUpCallback(int key, int x, int y)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			keyboardUpCallback(KGKey_left, x, y);
			break;
		case GLUT_KEY_RIGHT:
			keyboardUpCallback(KGKey_right, x, y);
			break;
		case GLUT_KEY_UP:
			keyboardUpCallback(KGKey_up, x, y);
			break;
		case GLUT_KEY_DOWN:
			keyboardUpCallback(KGKey_down, x, y);
			break;
		default:
			break;
		}
	}

	void keyboardControl::postUpdate()
	{
		// Empty the press and release lists:
		m_press.clear();
		m_released.clear();
	}

	bool keyboardControl::poll(const KG_KEY_TYPE &k, const KG_PRESS_TYPE &p)
	{
		switch (p)
		{
		case KG_DOWN:
			return (findElement(m_press, k) != m_press.end());
		case KG_PRESSED:
			return (findElement(m_pressed, k) != m_pressed.end());
		case KG_UP:
			return (findElement(m_released, k) != m_released.end());
		}

		return false;
	}

	bool keyboardControl::pollAny(const KG_PRESS_TYPE &p)
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

	std::vector<KG_KEY_TYPE>::iterator keyboardControl::findElement(
		std::vector<KG_KEY_TYPE> &v, const KG_KEY_TYPE &key)
	{
		std::vector<KG_KEY_TYPE>::iterator i;

		for (i = v.begin(); i < v.end(); ++i)
			if (*i == key)
				return i;

		return i;
	}
}
