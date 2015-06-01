#include <cstdio>

#include "engine.h"
#include "platformInclude.h"
#include "mesh.h"
#include "material.h"
#include "frog.h"
#include "misc.h"
#include "log.h"
#include "car.h"

using namespace kg;

int main(int argc, char **argv)
{
	// Initialise OpenGL stuff:
	initGL(&argc, argv);

	// Start Engine, and scene:
	Engine::pushScene(new Scene(), true);
	Scene *cScene = Engine::getCurrentScene();

	// Mesh pointers:
	Mesh *msp = Mesh::constructPlane(2, 2);
	Mesh *mrp = Mesh::constructPlane(8, 8);
	Mesh *mbp = Mesh::constructTerrain(40, 40, 25, 30, -0.0834f);

	// Setup Mesh Table:
	MeshTable::pushMesh("BigPlane", mbp);
	MeshTable::pushMesh("RiverPlane", mrp);
	MeshTable::pushMesh("SinglePlane", msp);
	MeshTable::pushMesh("Cube", Mesh::constructCube());
	MeshTable::pushMesh("Log", Mesh::constructCylinder(4, 8));
	MeshTable::pushMesh("Sphere", Mesh::constructSphere(7, 7));
	MeshTable::pushMesh("Circle", Mesh::constructCircle(8));

	/* Skybox:
	ObjectList &skybox = Engine::getPreScene();

	Object *left = skybox.addObject("Left", new Object()),
		*right = skybox.addObject("Right", new Object()),
		*top = skybox.addObject("Top", new Object()),
		*bottom = skybox.addObject("Bottom", new Object()),
		*back = skybox.addObject("Back", new Object()),
		*front = skybox.addObject("Front", new Object());

	// Note that getFromFile indexes files called multiple times! :D
	// Yay for efficiency:
	left->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	right->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	top->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	bottom->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	back->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	front->addProperty("Material", BasicMaterial::getFromFile("flat.mat"),
		true);
	
	left->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/negx.jpg")));
	right->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/posx.jpg")));
	top->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/posy.jpg")));
	bottom->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/negy.jpg")));
	back->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/negz.jpg")));
	front->getMaterial()->setTextureID(
		new unsigned(loadTexture("textures/skybox/posz.jpg")));

	left->addProperty("Mesh", msp, true);
	right->addProperty("Mesh", msp, true);
	top->addProperty("Mesh", msp, true);
	bottom->addProperty("Mesh", msp, true);
	back->addProperty("Mesh", msp, true);
	front->addProperty("Mesh", msp, true);

	left->addProperty("Transform",
		new Transform(Vector3(-1.0f, 0.0f, 0.0f)), true);
	right->addProperty("Transform",
		new Transform(Vector3(1.0f, 0.0f, 0.0f)), true);
	top->addProperty("Transform",
		new Transform(Vector3(0.0f, -1.0f, 0.0f)), true);
	bottom->addProperty("Transform",
		new Transform(Vector3(0.0f, 1.0f, 0.0f)), true);
	back->addProperty("Transform",
		new Transform(Vector3(0.0f, 0.0f, -1.0f)), true);
	front->addProperty("Transform",
		new Transform(Vector3(0.0f, 0.0f, 1.0f)), true);*/

	// Add floor:
	BasicMaterial *mat = BasicMaterial::getFromFile("flat.mat");
	mat->setTextureID(new unsigned(loadTexture("textures/ground.jpg")));
	Object *floor = cScene->sceneObjects.addObject("Floor",
		new Object());
	floor->addProperty("Material", mat, true);
	floor->addProperty("Mesh", mbp, true);
	floor->addProperty("Transform", new Transform(
		Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 100.0f)),
		true);

	// Add frog:
	FrogBase *frog = new FrogBase();
	cScene->sceneObjects.addObject("Frog", frog);

	// Add cars:
	const unsigned numCars = 40;
	unsigned lane = 0;

	Car *cars[numCars];

	std::string name = "Car ";

	for (unsigned i = 0; i < numCars; ++i)
	{
		cars[i] = new Car(lane % 2 != 0);

		cars[i]->getTransform()->m_pos.x = kg::getRandom(-48.0f, 48.0f);

		switch (lane)
		{
		case 0:
			cars[i]->getTransform()->m_pos.z = -30.0f;
			break;
		case 1:
			cars[i]->getTransform()->m_pos.z = -25.0f;
			break;
		case 2:
			cars[i]->getTransform()->m_pos.z = -19.0f;
			break;
		case 3:
			cars[i]->getTransform()->m_pos.z = -13.0f;
			break;
		}

		++lane;

		if (lane == 4)
			lane = 0;

		cScene->sceneObjects.addObject(name + i, cars[i]);
	}

	frog->m_numCars = numCars;
	frog->m_cars = cars;

	// Add logs:
	const unsigned numLogs = 35;
	lane = 0;

	Log *logs[numLogs];

	name = "Log ";

	for (unsigned i = 0; i < numLogs; ++i)
	{
		logs[i] = new Log(lane % 2 != 0);

		logs[i]->getTransform()->m_pos.x = kg::getRandom(-48.0f, 48.0f);

		switch (lane)
		{
		case 0:
			logs[i]->getTransform()->m_pos.z = 26.0f;
			break;
		case 1:
			logs[i]->getTransform()->m_pos.z = 22.0f;
			break;
		case 2:
			logs[i]->getTransform()->m_pos.z = 18.0f;
			break;
		case 3:
			logs[i]->getTransform()->m_pos.z = 14.0f;
			break;
		}

		++lane;

		if (lane == 4)
			lane = 0;

		cScene->sceneObjects.addObject(name + i, logs[i]);
	}

	frog->m_numLogs = numLogs;
	frog->m_logs = logs;

	// Add river:
	Object *river = cScene->sceneObjects.addObject("River",
		new Object());
	river->addProperty("Material",
		BasicMaterial::getFromFile("water.mat"), true);
	river->addProperty("Mesh", mrp, true);
	Transform *rt = new Transform(Vector3(0.0f, -0.87f, 21.0f),
		Vector3(100.0f, 1.0f, 19.0f));
	river->addProperty("Transform", rt, true);
	river->setTransparent(true);

	Engine::newMessage("A new round of frogger has begun!\n", 3.5f);

	printf("Starting main loop...\n");
	glutMainLoop();
}
