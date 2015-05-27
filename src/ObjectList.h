#ifndef objectList_h
#define objectList_h

#include "Object.h"

namespace kg
{
	struct ObjectList
	{
		// Desrtuctor:
		~ObjectList();

		// Methods:
		void update();
		void render();

		Object *addObject(const std::string &name, Object *object);
		bool removeObject(const std::string &name);
		bool renameObject(const std::string &name, const std::string &newName);

		template <typename T>
		T *getObject(const std::string &name);

	protected:
		// Protected Members:
		std::map<std::string, Object*> objects;
	};
}

#endif
