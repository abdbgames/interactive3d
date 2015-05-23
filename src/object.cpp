#include <cstdlib>
#include <string>

#include "Object.h"
#include "ObjectList.h"
#include "Engine.h"

bool checknullptr(kg::BaseProperty *in) { return (in == nullptr); }

namespace kg
{
	Object::Object()
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = nullptr;
		m_name = nullptr;
		m_renderType = KG_HIDE;
	}

	Object::Object(const char *name)
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = nullptr;
		m_renderType = KG_HIDE;
		setName(name);
	}

	Object::~Object()
	{
		// Destructor for all Objects:
		for (unsigned i = 0; i < properties.size(); ++i)
		{
			if (properties[i] != nullptr)
			{
				delete properties[i];
				properties[i] = nullptr;
			}
		}

		properties.clear();

		if (children)
		{
			delete children;
			children = nullptr;
		}

		if (m_name)
		{
			delete [] m_name;
			m_name = nullptr;
		}

		self = nullptr;
	}

	void Object::getSelf()
	{
		self = this;
	}

	void Object::setName(const char *name)
	{
		if (!name) return;

		if (m_name)
		{
			delete[] m_name;
			m_name = nullptr;
		}

		size_t len = strlen(name);

		m_name = new char[len];

		strcpy_s(m_name, len, name);
	}

	void Object::run()
	{
		if (self == nullptr)
		{
			getSelf();
			self->start();
		}

		self->update();

		// Update Method for all Properties:
		for (unsigned i = 0; i < properties.size(); ++i)
			// Attempt to update all Object properties:
			properties[i]->update();

		children->update();
	}

	void Object::render()
	{
		// No drawing if Object is hidden:
		if (m_renderType == KG_HIDE)
			return;


	}

	bool Object::addProperty(const char *name, BaseProperty *propertyType)
	{
		// Attaches a property to the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		if (p == nullptr)
		{
			properties.push_back(propertyType);
			properties[properties.size() - 1]->setName(name);
			return true;
		}

		p = nullptr;

		// Property never existed or could not be erased:
		return false;
	}

	bool Object::removeProperty(const char *name)
	{
		// Detaches a property from the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		if (p)
			delete p;

		p = nullptr;

		// Property never existed or could not be erased:
		return false;
	}

	bool Object::addChild(const char *name, Object *childObject)
	{
		// Attaches a child Object to the Object:
		return (children != nullptr) ? children->addObject(name, childObject)
			: false;
	}

	bool Object::removeChild(const char *name)
	{
		// Detaches a child Object from the Object:
		return (children != nullptr) ? children->removeObject(name) : false;
	}

	template <typename T>
	T *Object::getProperty(const char *name)
	{
		// Checks if an Object property exists and return a pointer to it:
		unsigned i = 0;

		while (i < properties.size() && strcmp(name, properties[i]->getName())
			!= 0)
			++i;

		return (i == properties.size()) ? nullptr :
			dynamic_cast<T*>(properties[i]);
	}

	template <typename T>
	T *Object::getChild(const char *name)
	{
		return children->getObject<T>(name);
	}
}
