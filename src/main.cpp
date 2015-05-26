#include <cstdio>

#include "Engine.h"
#include "PlatformInclude.h"

int main(int argc, char **argv)
{
	kg::initGL(&argc, argv);

	unsigned scene = kg::Engine::pushScene(new kg::Scene(), true);

	printf("Starting main loop...\n");

	glutMainLoop();

	kg::Engine::quit();
}
