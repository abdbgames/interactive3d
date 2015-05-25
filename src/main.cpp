#include "Engine.h"
#include "PlatformInclude.h"

int main(int argc, char **argv)
{
	kg::initGL(&argc, argv);

	unsigned scene = kg::Engine::pushScene(new kg::Scene(), true);

	glutMainLoop();

	kg::Engine::quit();
}
