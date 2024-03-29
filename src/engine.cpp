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
		m_s = m_sum = m_ft = 0.0f;
		m_currentScene = m_fc = m_fps = 0;

		// setup kg::Engine/OpenGL defaults:
		smoothShadingRefresh();
		textureRefresh();

		setLightState(KG_UNLIT);
		setDrawMode(KG_FILLED);

		// Seed random generator:
		std::srand((unsigned int)time(NULL));

		// Run update on all pre scene objects once (this is mainly intended
		// for skybox objects so it would be a waste of calls to do othersise):
		preScene.update();
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
		// Engine referance:
		static Engine &self = get();

		// Update delta time:
		static int t1 = -1;

		if (t1 == -1)
			t1 = glutGet(GLUT_ELAPSED_TIME);

		int t2 = glutGet(GLUT_ELAPSED_TIME);

		self.m_dt = (t2 - t1) / KG_MILLIS;

		t1 = t2;

		self.m_s += self.m_dt;

		// FPS Update:
		if (self.m_s >= 1.0f)
		{
			self.m_fps = get().m_fc;
			self.m_ft = get().m_sum / (float)get().m_fc;
			self.m_sum = 0.0f;
			self.m_fc = 0;
			self.m_s -= 1.0f;
		}

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

		// Toggle osd drawing:
		if (kg::keyboardControl::poll(KGKey_i, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_I, KG_DOWN))
			toggleOSD();

		// Toggle osd drawing:
		if (kg::keyboardControl::poll(KGKey_p, KG_DOWN) ||
			kg::keyboardControl::poll(KGKey_P, KG_DOWN))
			self.m_paused = !self.m_paused;

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
			self.m_cam.updateRot(mouseControl::pollMouseMoved()[1],
				mouseControl::pollMouseMoved()[0]);
		}
		
		if (mouseControl::poll(GLUT_RIGHT_BUTTON, KG_PRESSED))
		{
			get().m_cam.updateZoom(mouseControl::pollMouseMoved()[1]);
		}

		// Don't do anything if no current scene:
		if (!get().m_currentScene)
			// TODO scene validation:
			get().m_sceneList[self.m_currentScene]->update();

		// Update keyboard/mouse:
		keyboardControl::postUpdate();
		mouseControl::postUpdate();

		// Draw callback:
		glutPostRedisplay();
	}

	void Engine::renderCallback()
	{
		static Engine &self = get();

		glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT);

		// Clear screen:
		if (self.m_dirtyRendering)
			glClear(GL_DEPTH_BUFFER_BIT);
		else
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		self.m_cam.projectionGL();

		glPushMatrix();
		self.preScene.render();
		glPopMatrix();

		glLightfv(GL_LIGHT0, GL_POSITION,
			Vector3(100.0f, 100.0f, -100.0f).getV());
		glLightfv(GL_LIGHT0, GL_AMBIENT, Colour::Gray.getArray());
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Colour::Gray.getArray());
		glLightfv(GL_LIGHT0, GL_SPECULAR, Colour::White.getArray());

		if (self.m_lightMode != KG_UNLIT)
			glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		self.m_cam.modelViewGL();

		// Render origin axis:
		drawAxis(1.0f);

		// Don't do anything if no current scene:
		if (!self.m_currentScene)
			// TODO error checking for invalid scene:
			self.m_sceneList[self.m_currentScene]->render();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		// Draw the on screen display:
		if (self.m_osd)
		{
			std::string text = TITLE"\n";
			text = text + "FPS: " + self.m_fps + " f/s\n" +
				"Frame time: " + self.m_ft + " ms/f\n" +
				"Score: " + self.m_score + ", Lives: " + self.m_lives + '\n';

			std::vector<EText>::iterator i = self.m_messages.begin();

			while (i != self.m_messages.end())
			{
				// Print and update messages in message list:
				text = text + i->render;
				i->timeAlive += self.m_dt;

				// Doing this in a for loop throws strange behaviour:
				if (i->timeAllowed > 0.0f && i->timeAlive >= i->timeAllowed)
					i = self.m_messages.erase(i);
				else
					++i;
			}

			glColor3fv(Colour::Maroon.getArray());

			renderText(GLUT_BITMAP_8_BY_13, text, 0.0f, 0.0f);
		}

		glutSwapBuffers();

		glPopAttrib();

		// Frame counter:
		++self.m_fc;

		// Frame time counter:
		self.m_sum += self.m_dt;
	}

	EText &Engine::newMessage(const std::string &input, const float &time)
	{
		// Insert message to message list:
		static std::vector<EText> &m = get().m_messages;

		m.push_back(EText(input, time));

		return m[m.size() - 1];
	}

	void Engine::resizeCallback(int w, int h)
	{
		static Engine &self = get();

		// Update internal width height and aspect:
		self.m_width = w;
		self.m_height = h;
		self.m_aspect = (float)self.m_width / (float)self.m_height;

		// Reset viewport:
		glViewport(0, 0, w, h);
	}

	void Engine::setDrawMode(const KG_DRAW_MODE &dm)
	{
		static Engine &self = get();

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
			self.m_drawMode = dm;
	}

	void Engine::setLightState(const KG_LIGHT_MODE &lm)
	{
		static Engine &self = get();

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
			self.m_lightMode = lm;
	}

	void Engine::renderText(void *font, const std::string &str, const float &x,
		const float &y)
	{
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f, -1.0f,
			1.0f);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		float _x = x + 1.0f, _y = y + 10.0f;

		glRasterPos2f(_x, _y);

		for (unsigned i = 0; i < str.size(); ++i)
		{
			if (str.c_str()[i] == '\n')
			{
				_y += 13.2f;
				glRasterPos2f(_x, _y);
				continue;
			}

			glutBitmapCharacter(font, str.c_str()[i]);
		}

		glPopMatrix();
		glPopMatrix();
	}

	void Engine::setDrawTetxures(const bool &set)
	{
		static Engine &self = get();
		self.m_drawTextures = set;
		self.textureRefresh();
	}

	void Engine::setSmoothShading(const bool &set)
	{
		static Engine &self = get();
		self.m_smoothShading = set;
		self.smoothShadingRefresh();
	}

	void Engine::toggleDrawAxis()
	{
		static Engine &self = get();
		self.m_drawAxis = !self.m_drawAxis;
	}

	void Engine::toggleDrawTextures()
	{
		static Engine &self = get();
		setDrawTetxures(!self.m_drawTextures);
	}

	void Engine::toggleSmoothShading()
	{
		static Engine &self = get();
		setSmoothShading(!self.m_smoothShading);
	}

	void Engine::toggleDrawNormals()
	{
		static Engine &self = get();
		setDrawNormals(!self.m_drawNormals);
	}

	void Engine::toggleOSD()
	{
		static Engine &self = get();
		setOSD(!self.m_osd);
	}

	unsigned Engine::pushScene(Scene *s, const bool &setCurrent)
	{
		static Engine &self = get();

		// If you set this to NULL, you are Satan:
		if (!s) return 666;

		// Push scene onto scene list:
		self.m_sceneList.push_back(s);

		unsigned r = self.m_sceneList.size() - 1;

		// If we want to set new scene as the current one:
		if (setCurrent)
			self.m_currentScene = r;

		// Return scene ID we pushed:
		return r;
	}

	Scene *Engine::getScene(const unsigned &s)
	{
		static Engine &self = get();

		// Return null for invalid input:
		if (s >= self.m_sceneList.size())
			return NULL;

		// Return requested Scene:
		return self.m_sceneList[s];
	}

	Scene *Engine::getCurrentScene()
	{
		static Engine &self = get();

		// Return NULL for invalid input:
		if (self.m_currentScene >= self.m_sceneList.size())
			return NULL;

		// Return current Scene:
		return self.m_sceneList[self.m_currentScene];
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
