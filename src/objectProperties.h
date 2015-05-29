#ifndef objectProperties_h
#define objectProperties_h

#include <string>

#include "platformInclude.h"

namespace kg
{
	struct BaseProperty
	{
		// Constructors:
		BaseProperty() : m_name("Not set"), canDelete(true) {}
		BaseProperty(const std::string &name);
		
		virtual ~BaseProperty() {}

		// Virtual Methods:
		virtual void update() {}

		// Methods:
		void setName(const std::string &name);

		const std::string &getName() { return m_name; }
		
		bool canDelete;

	protected:
		// Protected Methods:
		std::string m_name;
	};
}

#endif
