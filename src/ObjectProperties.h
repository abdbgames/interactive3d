#ifndef objectProperties_h
#define objectProperties_h

#define NULL 0

#include <string>

namespace kg
{
	struct BaseProperty
	{
		// Constructors:
		BaseProperty() : m_name("Not set") {}
		BaseProperty(const std::string &name);

		// Desrtuctor:
		~BaseProperty() {}

		// Virtual Methods:
		virtual void update() {}

		// Methods:
		void setName(const std::string &name);

		const std::string &getName() { return m_name; }

	protected:
		// Protected Methods:
		std::string m_name;
	};
}

#endif
