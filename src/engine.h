#ifndef engine_h
#define engine_h

#include <vector>

#include "kgConstants.h"
#include "scene.h"

namespace kg
{
	struct Engine
	{
		static void updateCallback();
		static void renderCallback();
		static void resizeCallback(int w, int h);
		static void toggleDrawAxis();
		static void toggleDrawTextures();
		static void toggleSmoothShading();
		static void toggleDrawNormals();
		static void setDrawMode(const KG_DRAW_MODE &dm);
		static void setLightState(const KG_LIGHT_MODE &lm);
		static void setDrawAxis(const bool &set) { get().m_drawAxis = set; }
		static void setDrawTetxures(const bool &set);
		static void setSmoothShading(const bool &set);
		static void setDrawNormals(const bool &set)
			{ get().m_drawNormals = set; }

		static bool setCurrentScene(const unsigned &s);
		static bool getDrawAxisEnabled() { return get().m_drawAxis; }
		static bool getDrawTexturesEnabled() { return get().m_drawTextures; }
		static bool getDrawNormalsEnabled() { return get().m_drawNormals; }

		static Scene *getScene(const unsigned &s);
		static Scene *getCurrentScene();

		static KG_LIGHT_MODE getLightState() { return get().m_lightMode; }
		
		static KG_DRAW_MODE getDrawMode() { return get().m_drawMode; }

		static unsigned getWidth() { return get().m_width; }
		static unsigned getHeight() { return get().m_height; }
		static unsigned pushScene(Scene *s, const bool &setCurrent);

		static float getAspect() { return get().m_aspect; }
		static float getDeltaTime() { return get().m_dt; }

	private:
		Engine();
		~Engine();

		static Engine &get();

		KG_LIGHT_MODE m_lightMode;

		KG_DRAW_MODE m_drawMode;

		bool m_drawAxis, m_drawTextures, m_drawNormals, m_smoothShading,
			m_dirtyRendering;

		unsigned m_width, m_height, m_currentScene;

		float m_aspect, m_dt;

		std::vector<Scene*> m_sceneList;

		void textureRefresh();
		void smoothShadingRefresh();
	};
}

#endif

