#include <cstdlib>
#include <string>

#include "object.h"
#include "objectList.h"
#include "platformInclude.h"
#include "engine.h"

bool checknullptr(kg::BaseProperty *in) { return (in == NULL); }

namespace kg
{
	Object::Object()
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = NULL;
		m_mat = NULL;
		m_mesh = NULL;
		m_name = "Not set";
		m_transparent = false;
		m_renderType = KG_HIDE;
		m_lightType = KG_UNLIT;
	}

	Object::Object(const std::string &name)
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = NULL;
		m_mat = NULL;
		m_mesh = NULL;
		m_renderType = KG_HIDE;
		m_lightType = KG_UNLIT;
		m_transparent = false;
		setName(name);
	}

	Object::~Object()
	{
		// Destructor for all Properties:
		for (std::map<std::string, BaseProperty*>::iterator
			i = properties.begin(); i != properties.end(); ++i)
			if (i->second && i->second->canDelete)
				delete i->second;

		if (children)
			delete children;
	}

	void Object::getSelf()
	{
		// This is more important than you think,
		// It's actually for calling in the child instance:
		self = this;
	}

	void Object::setName(const std::string &name)
	{
		m_name = name;
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
		for (std::map<std::string, BaseProperty*>::iterator
			i = properties.begin(); i != properties.end(); ++i)
			i->second->update();

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

	bool Object::addProperty(const std::string &name,
		BaseProperty *propertyType, const bool &attemptDepend)
	{
		// If property is NULL, return not added:
		if (!propertyType)
			return false;
	
		// Attaches a property to the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		bool set = false;

		if (!p)
		{
			properties.insert(std::pair<std::string, BaseProperty*>(name,
				propertyType));
			propertyType->setName(name);
			set = true;
		}

		if (set && attemptDepend)
		{
			/* Attempt to put new property into dependency slot.
			Note that although std::string comparisons are O log(N) complexity
			I will be looking into string to intiger hashing to speed
			up this process (and other kge string lookups) in the future. */

			if (name == "Material")
			{
				m_mat = dynamic_cast<BasicMaterial*>(propertyType);
				return true;
			}
			if (name == "Mesh")
			{
				m_mesh = dynamic_cast<Mesh*>(propertyType);
				return true;
			}

		}

		// Property never existed or could not be erased:
		return false;
	}

	bool Object::removeProperty(const std::string &name)
	{
		// Detaches a property from the Object:
		BaseProperty *p = getProperty<BaseProperty>(name);

		if (p && p->canDelete)
			delete p;

		p = NULL;

		// Property never existed or could not be erased:
		return false;
	}

	Object *Object::addChild(const std::string &name, Object *childObject)
	{
		// Attaches a child Object to the Object:
		return (children) ? children->addObject(name, childObject)
			: NULL;
	}

	bool Object::deleteChild(const std::string &name)
	{
		// Detaches a child Object from the Object:
		return (children) ? children->deleteObject(name) : false;
	}

	bool Object::detachChild(const std::string &name)
	{
		// Detaches a child Object from the Object:
		return (children) ? children->deleteObject(name) : false;
	}

	template <typename T>
	T *Object::getProperty(const std::string &name)
	{
		std::map<std::string, BaseProperty*>::iterator
			i = properties.find(name);
		
		if (i == properties.end()) return NULL;

		return dynamic_cast<T*>(i->second);
	}

	template <typename T>
	T *Object::getChild(const std::string &name)
	{
		return children->getObject<T>(name);
	}
}

