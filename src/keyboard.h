#ifndef keyboard_h
#define keyboard_h

#include "platformInclude.h"
#include "kgConstants.h"

#include <vector>

namespace kg
{
	struct keyboardControl
	{
		static void keyboardCallback(KG_KEY_TYPE key, int x, int y);
		static void keyboardUpCallback(KG_KEY_TYPE key, int x, int y);
		static void specialCallback(int key, int x, int y);
		static void specialUpCallback(int key, int x, int y);
		static void postUpdate();

		static bool poll(const KG_KEY_TYPE &b, const KG_PRESS_TYPE &p);
		static bool pollAny(const KG_PRESS_TYPE &p);

		static std::vector<KG_KEY_TYPE> &getPressBuffer()
		{
			return m_press;
		}
		static std::vector<KG_KEY_TYPE> &getPressedBuffer()
		{
			return m_pressed;
		}
		static std::vector<KG_KEY_TYPE> &getReleasedBuffer()
		{
			return m_released;
		}

	protected:
		static std::vector<KG_KEY_TYPE> m_pressed, m_press, m_released;

		static std::vector<KG_KEY_TYPE>::iterator
			findElement(std::vector<KG_KEY_TYPE> &v,
			const KG_KEY_TYPE &key);
	};
}

#endif /* keyboard_h */
