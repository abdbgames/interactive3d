#ifndef scene_h
#define scene_h

#include "ObjectList.h"

namespace kg
{
	struct Scene
	{
		// Constructor:
		Scene();

		// Destructor:
		virtual ~Scene();

		// Methods:
		void update();
		void render();

		// Members:
		ObjectList *sceneObjects;
	};
}

#endif
