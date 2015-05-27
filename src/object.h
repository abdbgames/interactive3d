#ifndef object_h
#define object_h

#include "ObjectProperties.h"
#include "KGConstants.h"

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
		~Object();

		// Methods:
		void run();
		void render();
		void setName(const std::string &name);

		bool addProperty(const std::string &name, BaseProperty *propertyType);
		bool removeProperty(const std::string &name);
		bool addChild(const std::string &name, Object *childObject);
		bool removeChild(const std::string &name);

		const std::string &getName() { return m_name; }

		template <typename T>
		T *getProperty(const std::string &name);

		template <typename T>
		T *getChild(const std::string &name);

		// Virtual Methods:
		virtual void start() {}
		virtual void update() {}

	protected:
		// Protected Methods:
		void getSelf();

		// Protected Members:
		std::map<std::string, BaseProperty*> properties;

		std::string m_name;

		ObjectList *children;

		Object *self;

		KG_DRAW_MODE m_renderType;

		KG_LIGHT_MODE m_lightType;

		bool m_transparent;
	};
}

#endif
