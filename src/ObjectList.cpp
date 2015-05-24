#include "objectList.h"

bool checkNULL(kg::Object *in) { return (!in); }

namespace kg
{
	ObjectList::~ObjectList()
	{
		// Destructor for all Objects:
		for (unsigned i = 0; i < objects.size(); ++i)
		{
			if (objects[i])
			{
				delete objects[i];
				objects[i] = NULL;
			}
		}

		objects.clear();
	}

	void ObjectList::update()
	{
		// Updates all Objects:
		for (unsigned i = 0; i < objects.size(); ++i)
			if (objects[i])
				objects[i]->run();
	}

	void ObjectList::render()
	{
		// Renders all Objects:
		for (unsigned i = 0; i < objects.size(); ++i)
			if (objects[i])
				objects[i]->render();
	}

	bool ObjectList::addObject(const char *name, Object *object)
	{
		if (!object) return false;

		// Adds in an Object:
		if (!getObject<Object>(name))
		{
			objects.push_back(object);
			objects[objects.size() - 1]->setName(name);
			return true;
		}

		// Object never existed or could not be erased:
		return false;
	}

	bool ObjectList::removeObject(const char *name)
	{
		// Removes an Object:
		Object *o = getObject<Object>(name);

		if (o)
		{
			delete o;
			o = NULL;
			objects.erase(objects.begin(), std::remove_if(objects.begin(),
				objects.end(), checkNULL));
			return true;
		}

		// Object never existed or could not be erased:
		return false;
	}

	template <typename T>
	T *ObjectList::getObject(const char *name)
	{
		// Finds and returns an instance of an Object:
		unsigned i = 0;

		while (i < objects.size() && strcmp(name, objects[i]->getName()) != 0)
			++i;

		return (i == objects.size()) ? NULL : dynamic_cast<T*>(objects[i]);
	}

	bool ObjectList::renameObject(const char *name, const char *newName)
	{
		// Renames an Object, quite a complex process actually... :P
		Object *o = getObject<Object>(name);

		if (o)
		{
			o->setName(newName);
			return true;
		}

		// Couldn't find the Object or the new name was already taken:
		return false;
	}
}
