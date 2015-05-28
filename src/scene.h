#ifndef scene_h
#define scene_h

#include "objectList.h"

namespace kg
{
	struct Scene
	{
		void update();
		void render();

		ObjectList sceneObjects;
	};
}

#endif
