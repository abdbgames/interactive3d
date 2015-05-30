#include <cstdlib>
#include <time.h>
#include <cstdio>

#include "engine.h"
#include "platformInclude.h"
#include "mesh.h"
#include "misc.h"
#include "keyboard.h"
#include "mouse.h"

namespace kg
{
	Engine::Engine()
	{
		printf("Starting KGE!\n");

		// Default Engine values:
		m_drawAxis = false;
		m_smoothShading = true;
		m_drawTextures = true;
		m_dirtyRendering = false;
		m_drawNormals = false;
		m_osd = true;
		m_width = 1024;
		m_height = 768;
		m_aspect = (float)m_width / (float)m_height;
		m_currentScene = 0;

		// setup kg::Engine/OpenGL defaults:
		smoothShadingRefresh();
		textureRefresh();

		setLightState(KG_UNLIT);
		setDrawMode(KG_FILLED);

		// Seed random generator:
		std::srand((unsigned int)time(NULL));
	}

	Engine::~Engine()
	{
		printf("Now cleaning KGE.\n");

		// Delete Scenes:
		for (unsigned i = 0; i < m_sceneList.size(); ++i)
			delete m_sceneList[i];

		// Cleanup:
		MeshTable::cleanup();

		exit(EXIT_SUCCESS);
	}

	Engine &Engine::get()
	{
		// Singelton:
		static Engine e;
		return e;
	}

	void Engine::updateCallback()
	{
		// Update delta time:
		static int t1 = -1;

		if (t1 == -1)
			t1 = glutGet(GLUT_ELAPSED_TIME);

		int t2 = glutGet(GLUT_ELAPSED_TIME);

		get().m_dt = (t2 - t1) / 1000.0f;

		t1 = t2;

		// Check if program should be quit:
		if (keyboardControl::poll(KGKey_q, KG_DOWN) ||
			keyboardControl::poll(KGKey_Q, KG_DOWN) ||
			keyboardControl::poll(KGKey_esc, KG_DOWN))
			exit(EXIT_SUCCESS);

		// Toggle axis drawing:
		if (kg::keyboardControl::poll(KGKey_o, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_O, KG_DOWN))
			toggleDrawAxis();

		// Toggle normal drawing:
		if (kg::keyboardControl::poll(KGKey_n, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_N, KG_DOWN))
			toggleDrawNormals();

		// Toggle texture drawing:
		if (kg::keyboardControl::poll(KGKey_t, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_T, KG_DOWN))
			toggleDrawTextures();

		if (kg::keyboardControl::poll(KGKey_l, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_L, KG_DOWN))
			get().setLightState((get().m_lightMode == KG_UNLIT) ? KG_FULL :
				KG_UNLIT);

		// If we are hitting a mouse button, lock the mouse to that position
		// and hide the cursor, otherwise unlock and set cursor to "clickable":
		if (kg::mouseControl::pollAny(KG_PRESSED))
		{
			// The locking itself always occurs at the end of an update,
			// so it's safe to put this call anywhere:
			kg::mouseControl::lockMouse(kg::mouseControl::m_x,
				kg::mouseControl::m_y);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else
		{
			kg::mouseControl::unlockMouse();
			glutSetCursor(GLUT_CURSOR_INFO);
		}

		// Update camera movement:
		if (mouseControl::poll(GLUT_LEFT_BUTTON, KG_PRESSED))
		{
			get().m_cam.updateRot(mouseControl::pollMouseMoved()[1],
				mouseControl::pollMouseMoved()[0]);
		}
		
		if (mouseControl::poll(GLUT_RIGHT_BUTTON, KG_PRESSED))
		{
			get().m_cam.updateZoom(mouseControl::pollMouseMoved()[1]);
		}

		// Don't do anything if no current scene:
		if (!get().m_currentScene)
			// TODO scene validation:
			get().m_sceneList[get().m_currentScene]->update();

		// Update keyboard/mouse:
		keyboardControl::postUpdate();
		mouseControl::postUpdate();

		// Draw callback:
		glutPostRedisplay();
	}

	void Engine::renderCallback()
	{
		glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT);

		// Clear screen:
		if (!get().m_dirtyRendering)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		get().m_cam.projectionGL();
		get().m_cam.modelViewGL();

		// Render origin axis:
		drawAxis(1.0f);

		// Don't do anything if no current scene:
		if (!get().m_currentScene)
			// TODO error checking for invalid scene:
			get().m_sceneList[get().m_currentScene]->render();

		// For drawing hud elements:
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f, -1.0f,
			1.0f);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glRasterPos2f(2.0f, 12.0f);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'K');
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		glPopMatrix();

		glutSwapBuffers();

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
