#include <cstdio>

#include "engine.h"
#include "platformInclude.h"
#include "mesh.h"

int main(int argc, char **argv)
{
	kg::initGL(&argc, argv);

	kg::Engine::pushScene(new kg::Scene(), true);

	kg::Scene *cScene = kg::Engine::getCurrentScene();

	kg::Object *floor = cScene->sceneObjects.addObject("Floor",
		new kg::Object());

	// TODO mesh table:
	floor->addProperty("FloorMesh", kg::Mesh::constructPlane(100, 100));

	printf("Starting main loop...\n");

	glutMainLoop();

	kg::Engine::quit();
}
