#ifndef engine_h
#define engine_h

#include "KGConstants.h"

namespace kg
{
	struct Engine
	{
		static void updateCallback();
		static void renderCallback();
		static void resizeCallback(int w, int h);
		static void toggleDrawAxis();

		static bool drawAxisEnabled() { return get().m_drawAxis; }

		static KG_LIGHT_MODE getLightState() { return get().m_lightMode; }
		
		static KG_DRAW_MODE getDrawMode() { return get().m_drawMode; }

		static unsigned getWidth() { return get().m_width; }
		static unsigned getHeight() { return get().m_height; }

		static float getAspect() { return get().m_aspect; }

	private:
		Engine();
		~Engine() {}

		static Engine &get();

		KG_LIGHT_MODE m_lightMode;

		KG_DRAW_MODE m_drawMode;

		bool m_drawAxis;

		unsigned m_width, m_height;

		float m_aspect;
	};
}

#endif
