#include <string>

#include "ObjectProperties.h"
#include "Engine.h"

namespace kg
{
	BaseProperty::BaseProperty(const char *name)
	{
		setName(name);
	}

	BaseProperty::~BaseProperty()
	{
		if (m_name != NULL)
			delete[] m_name;
	}

	void BaseProperty::setName(const char *name)
	{
		if (!name) return;

		if (m_name)
			delete[] m_name;

		size_t len = strlen(name);

		m_name = new char[len];

		strcpy_s(m_name, len, name);
	}
}
