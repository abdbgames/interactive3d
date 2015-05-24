#include <cstdlib>
#include <string>

#include "Object.h"
#include "ObjectList.h"
#include "PlatformInclude.h"
#include "Engine.h"

bool checknullptr(kg::BaseProperty *in) { return (in == NULL); }

namespace kg
{
	Object::Object()
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = NULL;
		m_name = NULL;
		m_transparent = false;
		m_renderType = KG_HIDE;
		m_lightType = KG_UNLIT;
	}

	Object::Object(const char *name)
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = NULL;
		m_renderType = KG_HIDE;
		m_lightType = KG_UNLIT;
		m_transparent = false;
		setName(name);
	}

	Object::~Object()
	{
		// Destructor for all Objects:
		for (unsigned i = 0; i < properties.size(); ++i)
			if (properties[i])
				delete properties[i];

		properties.clear();

		if (children)
			delete children;

		if (m_name)
			delete [] m_name;
	}

	void Object::getSelf()
	{
		// This is more important than you think,
		// It's actually for calling in the child instance:
		self = this;
	}

	void Object::setName(const char *name)
	{
		if (!name) return;

		if (m_name)
		{
			delete[] m_name;
			m_name = NULL;
		}

		size_t len = strlen(name);

		m_name = new char[len];

		strcpy_s(m_name, len, name);
	}

	void Object::run()
	{
		if (!self)
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
		// Push local matrix:
		glPushMatrix();

		// Run transform calls:

		// No drawing if Object is hidden:
		if (m_renderType == KG_HIDE)
		{
			glPopMatrix();
			return;
		}

		// Run material calls:


		// Render mesh:


		// Pop local Matrix:
		glPopMatrix();
	}

	bool Object::addProperty(const char *name, BaseProperty *propertyType)
	{
		// Attaches a property to the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		if (p == NULL)
		{
			properties.push_back(propertyType);
			properties[properties.size() - 1]->setName(name);
			return true;
		}

		p = NULL;

		// Property never existed or could not be erased:
		return false;
	}

	bool Object::removeProperty(const char *name)
	{
		// Detaches a property from the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		if (p)
			delete p;

		p = NULL;

		// Property never existed or could not be erased:
		return false;
	}

	bool Object::addChild(const char *name, Object *childObject)
	{
		// Attaches a child Object to the Object:
		return (children != NULL) ? children->addObject(name, childObject)
			: false;
	}

	bool Object::removeChild(const char *name)
	{
		// Detaches a child Object from the Object:
		return (children != NULL) ? children->removeObject(name) : false;
	}

	template <typename T>
	T *Object::getProperty(const char *name)
	{
		// Checks if an Object property exists and return a pointer to it:
		unsigned i = 0;

		while (i < properties.size() && strcmp(name, properties[i]->getName())
			!= 0)
			++i;

		return (i == properties.size()) ? NULL :
			dynamic_cast<T*>(properties[i]);
	}

	template <typename T>
	T *Object::getChild(const char *name)
	{
		return children->getObject<T>(name);
	}
}
