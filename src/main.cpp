#include <cstdio>

#include "engine.h"
#include "platformInclude.h"
#include "mesh.h"
#include "material.h"
#include "frog.h"
#include "misc.h"

int main(int argc, char **argv)
{
	// Initialise OpenGL stuff:
	kg::initGL(&argc, argv);

	// Start Engine, and scene:
	kg::Engine::pushScene(new kg::Scene(), true);
	kg::Scene *cScene = kg::Engine::getCurrentScene();

	// Setup Mesh Table:
	kg::MeshTable::pushMesh("BigPlane", kg::Mesh::constructTerrain(
		40, 40, 25, 30, -0.0834f));
	kg::MeshTable::pushMesh("RiverPlane", kg::Mesh::constructPlane(10, 10));
	kg::MeshTable::pushMesh("SinglePlane", kg::Mesh::constructPlane(4, 4));
	kg::MeshTable::pushMesh("Cube", kg::Mesh::constructCube());

	// Add floor:
	kg::BasicMaterial *mat = kg::BasicMaterial::getFromFile("flat.mat");
	mat->setTextureID(new unsigned(kg::loadTexture("textures/ground.jpg")));
	kg::Object *floor = cScene->sceneObjects.addObject("Floor",
		new kg::Object());
	floor->addProperty("Mesh", kg::MeshTable::find("BigPlane"), true);
	floor->addProperty("Material", mat, true);
	floor->addProperty("Transform", new kg::Transform(
		kg::Vector3(0.0f, 0.0f, 0.0f), kg::Vector3(100.0f, 100.0f, 100.0f)),
		true);

	// Add frog:
	FrogBase *frog = new FrogBase();
	cScene->sceneObjects.addObject("Frog", frog);

	// Add river:
	kg::Object *river = cScene->sceneObjects.addObject("River",
		new kg::Object());
	river->addProperty("Material",
		kg::BasicMaterial::getFromFile("water.mat"), true);
	river->addProperty("Mesh", kg::MeshTable::find("RiverPlane"), true);
	kg::Transform *rt = new kg::Transform(kg::Vector3(0.0f, -0.87f, 21.0f),
		kg::Vector3(100.0f, 1.0f, 19.0f));
	river->addProperty("Transform", rt, true);
	river->setTransparent(true);

	printf("Starting main loop...\n");
	glutMainLoop();
}
