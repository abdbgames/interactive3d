#include <cstdlib>
#include <time.h>

#include "Engine.h"
#include "PlatformInclude.h"

namespace kg
{
	Engine::Engine()
	{
		m_lightMode = KG_FULL;
		m_drawMode = KG_FILLED;
		m_drawAxis = false;
		m_width = 1024;
		m_height = 768;
		m_aspect = (float)m_width / (float)m_height;

		// Seed random generator:
		std::srand((unsigned int)time(nullptr));
	}

	Engine &Engine::get()
	{
		static Engine e;
		return e;
	}

	void Engine::updateCallback()
	{
		
	}

	void Engine::renderCallback()
	{
		
	}

	void Engine::resizeCallback(int w, int h)
	{
		get().m_width = w;
		get().m_height = h;
		get().m_aspect = (float)get().m_width / (float)get().m_height;
	}

	void Engine::toggleDrawAxis()
	{
		get().m_drawAxis = !get().m_drawAxis;
	}
}