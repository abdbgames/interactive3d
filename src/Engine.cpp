#include <cstdlib>
#include <time.h>
#include <cstdio>

#include "Engine.h"
#include "PlatformInclude.h"
#include "Mesh.h"

namespace kg
{
	Engine::Engine()
	{
		printf("Starting KGE!\n");

		// Default Engine values:
		m_lightMode = KG_FULL;
		m_drawMode = KG_FILLED;
		m_drawAxis = false;
		m_smoothShading = true;
		m_drawTextures = true;
		m_drawNormals = false;
		m_width = 1024;
		m_height = 768;
		m_aspect = (float)m_width / (float)m_height;
		m_currentScene = 0;

		// setup kg::Engine/OpenGL defaults:
		smoothShadingRefresh();
		textureRefresh();

		// Seed random generator:
		std::srand((unsigned int)time(NULL));
	}

	Engine::~Engine()
	{
		printf("Now cleaning KGE.\n");

		// Delete Scenes:
		for (unsigned i = 0; i < m_sceneList.size(); ++i)
			delete m_sceneList[i];
	}

	Engine &Engine::get()
	{
		// Singelton:
		static Engine e;
		return e;
	}

	void Engine::updateCallback()
	{
		// Don't do anything if no current scene:
		if (!get().m_currentScene) return;

		// Don't do anything for invalid input:
		if (get().m_currentScene >= get().m_sceneList.size()) return;

		// Update current Scene:
		get().m_sceneList[get().m_currentScene]->update();
	}

	void Engine::renderCallback()
	{
		glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT);

		// Don't do anything if no current scene:
		if (!get().m_currentScene) return;

		// Don't do anything for invalid input:
		if (get().m_currentScene >= get().m_sceneList.size()) return;

		// Render current Scene:
		get().m_sceneList[get().m_currentScene]->render();

		glPopAttrib();
	}

	void Engine::resizeCallback(int w, int h)
	{
		// Update internal width height and aspect:
		get().m_width = w;
		get().m_height = h;
		get().m_aspect = (float)get().m_width / (float)get().m_height;

		// Reset viewport:
		glViewport(0, 0, w, h);
	}
	
	void Engine::quit()
	{
		MeshTable::cleanup();

		exit(EXIT_SUCCESS);
	}

	void Engine::setDrawMode(const KG_DRAW_MODE &dm)
	{
		bool change = true;

		switch (dm)
		{
		case KG_FILLED:
			printf("Setting filled pollygon rendering mode,"
				" with backface culling.\n");
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		case KG_FILLED_NOCULL:
			printf("Setting filled pollygon rendering mode,"
				" with no backface culling.\n");
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case KG_WIRE:
			printf("Setting wireframe rendering mode\n");
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case KG_POINTS:
			printf("Setting vertex points rendering mode\n");
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		default:
			printf("This cannot be set as the engine rendering mode!\n"
				"Falling back to last good draw mode!\n");
			change = false;
			break;
		}

		if (change)
			get().m_drawMode = dm;
	}

	void Engine::setLightState(const KG_LIGHT_MODE &lm)
	{
		bool change = true;

		switch (lm)
		{
		case KG_FULL:
			printf("Turning on full lighting.\n");
			glEnable(GL_LIGHTING);
			break;
		case KG_DIR:
			printf("Turning on directional lighting only.\n");
			glEnable(GL_LIGHTING);
			break;
		case KG_UNLIT:
			printf("Turning off lighting.\n");
			glDisable(GL_LIGHTING);
			break;
		default:
			printf("Unable to change engine lighting mode!\n"
				"Falling back to last good lighting mode!\n");
			change = false;
			break;
		}

		if (change)
			get().m_lightMode = lm;
	}

	void Engine::setDrawTetxures(const bool &set)
	{
		get().m_drawTextures = set;
		get().textureRefresh();
	}

	void Engine::setSmoothShading(const bool &set)
	{
		get().m_smoothShading = set;
		get().smoothShadingRefresh();
	}

	void Engine::toggleDrawAxis()
	{
		get().m_drawAxis = !get().m_drawAxis;
	}

	void Engine::toggleDrawTextures()
	{
		setDrawTetxures(!get().m_drawTextures);
	}

	void Engine::toggleSmoothShading()
	{
		setSmoothShading(!get().m_smoothShading);
	}

	void Engine::toggleDrawNormals()
	{
		setDrawNormals(!get().m_drawNormals);
	}

	unsigned Engine::pushScene(Scene *s, const bool &setCurrent)
	{
		// If you set this to NULL, you are Satan:
		if (!s) return 666;

		// Push scene onto scene list:
		get().m_sceneList.push_back(s);

		unsigned r = get().m_sceneList.size() - 1;

		// If we want to set new scene as the current one:
		if (setCurrent)
			get().m_currentScene = r;

		// Return scene ID we pushed:
		return r;
	}

	Scene *Engine::getScene(const unsigned &s)
	{
		// Return null for invalid input:
		if (s >= get().m_sceneList.size())
			return NULL;

		// Return requested Scene:
		return get().m_sceneList[s];
	}

	Scene *Engine::getCurrentScene()
	{
		// Return NULL if no current scene:
		if (!get().m_currentScene)
			return NULL;

		// Return NULL for invalid input:
		if (get().m_currentScene >= get().m_sceneList.size())
			return NULL;

		// Return current Scene:
		return get().m_sceneList[get().m_currentScene];
	}

	void Engine::textureRefresh()
	{
		// Enable or disable OpenGL textures:
		(m_drawTextures) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	}

	void Engine::smoothShadingRefresh()
	{
		// Enable or disable OpenGL textures:
		glShadeModel((m_smoothShading) ? GL_SMOOTH : GL_FLAT);
	}
}
