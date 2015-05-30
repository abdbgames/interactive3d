#include "objectProperties.h"

namespace kg
{
	BaseProperty::BaseProperty(const std::string &name)
	{
		m_name = name;
		canDelete = true;
	}

	BaseProperty::~BaseProperty()
	{
		printf("Cleaning property %s.\n", m_name.c_str());
	}

	void BaseProperty::setName(const std::string &name)
	{
		m_name = name;
	}
}
