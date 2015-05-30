#ifndef object_h
#define object_h

#include "objectProperties.h"
#include "kgConstants.h"
#include "mesh.h"
#include "material.h"
#include "transform.h"

#include <map>
#include <algorithm>

namespace kg
{
	struct ObjectList;

	struct Object
	{
		// Constructors:
		Object();
		Object(const std::string &name);

		// Destructor:
		virtual ~Object();

		void run();
		void render();
		void setName(const std::string &name);
		void setHidden(const bool &hide) { m_hidden = hide; }
		void setTransparent(const bool &a) { m_transparent = a; }

		bool addProperty(const std::string &name, BaseProperty *propertyType,
			const bool &attemptDepend);
		bool removeProperty(const std::string &name);
		bool deleteChild(const std::string &name);
		bool detachChild(const std::string &name);

		Object *addChild(const std::string &name, Object *childObject);

		const std::string &getName() { return m_name; }

		template <typename T>
		T *getProperty(const std::string &name);

		template <typename T>
		T *getChild(const std::string &name);

		BasicMaterial *getMaterial() { return m_mat; }

		Mesh *getMesh() { return m_mesh; }

		Transform *getTransform() { return m_transform; }

		Transform2D *getTransform2D() { return m_transform2D; }

		virtual void start() {}
		virtual void update() {}

	protected:
		std::map<std::string, BaseProperty*> properties;

		std::string m_name;

		ObjectList *children;

		Object *self;

		bool m_hidden, m_lit, m_transparent;

		// Possible dependencies:
		BasicMaterial *m_mat;

		Mesh *m_mesh;

		Transform *m_transform;

		Transform2D *m_transform2D;
	};
}

#endif

