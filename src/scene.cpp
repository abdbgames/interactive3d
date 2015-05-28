#include "scene.h"

namespace kg
{
	void Scene::update()
	{
		sceneObjects.update();
	}

	void Scene::render()
	{
		sceneObjects.render();
	}
}
