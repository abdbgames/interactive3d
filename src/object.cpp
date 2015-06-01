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
		m_transform = NULL;
		m_transform2D = NULL;
		m_name = "Not set";
		m_transparent = false;
		m_hidden = false;
		m_lit = false;
	}

	Object::Object(const std::string &name)
	{
		// Constructor for all Objects:
		children = new ObjectList;
		self = NULL;
		m_mat = NULL;
		m_mesh = NULL;
		m_transform = NULL;
		m_transform2D = NULL;
		m_hidden = false;
		m_lit = false;
		m_transparent = false;
		setName(name);
	}

	Object::~Object()
	{
		// Destructor for all Properties:
		printf("Cleaning %s properties.\n", m_name.c_str());
		for (std::map<std::string, BaseProperty*>::iterator
			i = properties.begin(); i != properties.end(); ++i)
			if (i->second && i->second->canDelete)
				delete i->second;

		printf("Cleaning %s children.\n", m_name.c_str());
		if (children)
			delete children;

		printf("Cleaning %s complete.\n", m_name.c_str());
	}

	void Object::setName(const std::string &name)
	{
		m_name = name;
	}

	void Object::run()
	{
		if (!self)
		{
			self = this;
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
		glPushAttrib(GL_CURRENT_BIT);

		if (m_transparent)
		{
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		// Disable textures, material will add this if necesary:
		glDisable(GL_TEXTURE_2D);

		// Enable lighting:
		if (m_lit && Engine::getLightState() != KG_UNLIT)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);

		// Run transform calls:
		if (m_transform)
			m_transform->glStuff();
		else if (m_transform2D)
			m_transform2D->glStuff();

		// No drawing if Object is hidden:
		if (!m_hidden)
		{
			// Render properties, make sure material is pushed before mesh!
			for (std::map<std::string, BaseProperty*>::iterator
				i = properties.begin(); i != properties.end(); ++i)
				i->second->render();
		}

		// Render Children:
		children->render();
		
		glDepthMask(GL_TRUE);

		// Pop local Matrix:
		glPopMatrix();
		glPopAttrib();
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
			if (name == "Transform")
			{
				m_transform = dynamic_cast<Transform*>(propertyType);
				return true;
			}
			if (name == "Transform2D")
			{
				m_transform2D = dynamic_cast<Transform2D*>(propertyType);
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
