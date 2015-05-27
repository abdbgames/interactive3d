#include "objectList.h"

bool checkNULL(kg::Object *in) { return (!in); }

namespace kg
{
	ObjectList::~ObjectList()
	{
		// Destructor for all Objects:
		for (std::map<std::string, Object*>::iterator i = objects.begin();
			i != objects.end(); ++i)
			if (i->second)
				delete i->second;
	}

	void ObjectList::update()
	{
		// Updates all Objects:
		for (std::map<std::string, Object*>::iterator i = objects.begin();
			i != objects.end(); ++i)
			if (i->second)
				i->second->run();
	}

	void ObjectList::render()
	{
		// Renders all Objects:
		for (std::map<std::string, Object*>::iterator i = objects.begin();
			i != objects.end(); ++i)
			if (i->second)
				i->second->render();
	}

	Object *ObjectList::addObject(const std::string &name, Object *object)
	{
		if (!object) return NULL;

		// Adds in an Object:
		if (!getObject<Object>(name))
		{
			objects.insert(std::pair<std::string, Object*>(name, object));
			object->setName(name);
			return object;
		}

		// Object never existed or could not be added:
		return NULL;
	}

	bool ObjectList::removeObject(const std::string &name)
	{
		std::map<std::string, Object*>::iterator i = objects.find(name);

		if (i == objects.end()) return false;

		delete i->second;
		i->second = NULL; // Just to be thread safe in future mainly...

		objects.erase(i);

		return true;
	}

	template <typename T>
	T *ObjectList::getObject(const std::string &name)
	{
		// Finds and returns an instance of an Object:
		unsigned i = 0;

		while (i < objects.size() && strcmp(name, objects[i]->getName()) != 0)
			++i;

		return (i == objects.size()) ? NULL : dynamic_cast<T*>(objects[i]);
	}

	bool ObjectList::renameObject(const std::string &name,
		const std::string &newName)
	{
		// Renames an Object:
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
