#ifndef engine_h
#define engine_h

#include <vector>
#include <string>

#include "kgConstants.h"
#include "scene.h"
#include "camera.h"

namespace kg
{
	struct EText
	{
		EText(const std::string &input, const float &time) : render(input),
			timeAlive(0.0f), timeAllowed(time) {}

		std::string render;
		float timeAlive, timeAllowed;
	};

	struct Engine
	{
		static void updateCallback();
		static void renderCallback();
		static void resizeCallback(int w, int h);
		static void toggleDrawAxis();
		static void toggleDrawTextures();
		static void toggleSmoothShading();
		static void toggleDrawNormals();
		static void toggleOSD();
		static void setDrawMode(const KG_DRAW_MODE &dm);
		static void setLightState(const KG_LIGHT_MODE &lm);
		static void setDrawAxis(const bool &set) { get().m_drawAxis = set; }
		static void setDrawTetxures(const bool &set);
		static void setSmoothShading(const bool &set);
		static void setOSD(const bool &set) { get().m_osd = set; }
		static void renderText(void *font, const std::string &str,
			const float &x, const float &y);
		static void setDrawNormals(const bool &set)
			{ get().m_drawNormals = set; }
		static void setCameraLookAt(Vector3 *pos)
			{ get().m_cam.m_lookAt = pos; }
		static void setCameraLookAt(Object *la);
		static void setLives(const unsigned &l) { get().m_lives = l; }
		static void setScore(const unsigned &s) { get().m_score = s; }

		static EText &newMessage(const std::string &input, const float &time);

		static bool setCurrentScene(const unsigned &s);
		static bool getDrawAxisEnabled() { return get().m_drawAxis; }
		static bool getDrawTexturesEnabled() { return get().m_drawTextures; }
		static bool getDrawNormalsEnabled() { return get().m_drawNormals; }

		static Scene *getScene(const unsigned &s);
		static Scene *getCurrentScene();

		static Camera &getCamera() { return get().m_cam; }

		static KG_LIGHT_MODE getLightState() { return get().m_lightMode; }
		
		static KG_DRAW_MODE getDrawMode() { return get().m_drawMode; }

		static unsigned getWidth() { return get().m_width; }
		static unsigned getHeight() { return get().m_height; }
		static unsigned pushScene(Scene *s, const bool &setCurrent);

		static float getAspect() { return get().m_aspect; }
		static float getDeltaTime() { return get().m_dt; }

		static ObjectList &getPreScene() { return get().preScene; }

	private:
		Engine();
		~Engine();

		static Engine &get();

		KG_LIGHT_MODE m_lightMode;

		KG_DRAW_MODE m_drawMode;

		Camera m_cam;

		bool m_drawAxis, m_drawTextures, m_drawNormals, m_smoothShading,
			m_dirtyRendering, m_osd, m_paused;

		unsigned m_width, m_height, m_currentScene, m_fc, m_fps, m_lives,
			m_score;

		float m_aspect, m_dt, m_s, m_sum, m_ft;

		std::vector<Scene*> m_sceneList;

		std::vector<EText> m_messages;

		ObjectList preScene;

		void textureRefresh();
		void smoothShadingRefresh();
	};
}

#endif

