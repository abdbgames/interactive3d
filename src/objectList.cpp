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
			else
				objects.erase(i++);
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

	bool ObjectList::deleteObject(const std::string &name)
	{
		std::map<std::string, Object*>::iterator i = objects.find(name);

		if (i == objects.end()) return false;

		delete i->second;
		i->second = NULL;

		return true;
	}

	bool ObjectList::detachObject(const std::string &name)
	{
		std::map<std::string, Object*>::iterator i = objects.find(name);

		if (i == objects.end()) return false;

		i->second = NULL;

		return true;
	}

	template <typename T>
	T *ObjectList::getObject(const std::string &name)
	{
		// Finds and returns an instance of an Object:
		std::map<std::string, Object*>::iterator i = objects.find(name);

		return (i == objects.end()) ? NULL : dynamic_cast<T*>(i->second);
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
