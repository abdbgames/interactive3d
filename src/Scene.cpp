#include "Scene.h"

namespace kg
{
	Scene::Scene()
	{
		// Defualt constructor for a scene:
		sceneObjects = new ObjectList;
	}

	Scene::~Scene()
	{
		// Default destructor for a scene:
		delete sceneObjects;
	}

	void Scene::update()
	{
		sceneObjects->update();
	}
}
