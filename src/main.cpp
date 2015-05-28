#include <cstdio>

#include "engine.h"
#include "platformInclude.h"
#include "mesh.h"
#include "material.h"

int main(int argc, char **argv)
{
	kg::initGL(&argc, argv);

	kg::Engine::pushScene(new kg::Scene(), true);

	kg::Scene *cScene = kg::Engine::getCurrentScene();

	kg::Object *floor = cScene->sceneObjects.addObject("Floor",
		new kg::Object());

	// TODO mesh table:
	floor->addProperty("Mesh", kg::Mesh::constructPlane(40, 40), true);
	floor->addProperty("Material", kg::BasicMaterial::getFromFile("car.mat"),
		true);

	printf("Starting main loop...\n");
	glutMainLoop();
}
