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

		bool addObject(const char *name, Object *object);
		bool removeObject(const char *name);
		bool renameObject(const char *name, const char *newName);

		template <typename T>
		T *getObject(const char *name);

	protected:
		// Protected Members:
		std::vector<Object*> objects;
	};
}

#endif
