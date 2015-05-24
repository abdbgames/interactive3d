#ifndef object_h
#define object_h

#include "ObjectProperties.h"
#include "KGConstants.h"

#include <vector>
#include <algorithm>

namespace kg
{
	struct ObjectList;

	struct Object
	{
		// Constructors:
		Object();
		Object(const char *name);

		// Destructor:
		~Object();

		// Methods:
		void run();
		void render();
		void setName(const char *name);

		bool addProperty(const char *name, BaseProperty *propertyType);
		bool removeProperty(const char *name);
		bool addChild(const char *name, Object *childObject);
		bool removeChild(const char *name);

		const char *getName() { return m_name; }

		template <typename T>
		T *getProperty(const char *name);

		template <typename T>
		T *getChild(const char *name);

		// Virtual Methods:
		virtual void start() {}
		virtual void update() {}

	protected:
		// Protected Methods:
		void getSelf();

		// Protected Members:
		std::vector<BaseProperty*> properties;

		char *m_name;

		ObjectList *children;

		Object *self;

		KG_DRAW_MODE m_renderType;

		KG_LIGHT_MODE m_lightType;

		bool m_transparent;
	};
}

#endif
