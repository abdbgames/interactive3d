#include "objectProperties.h"

namespace kg
{
	BaseProperty::BaseProperty(const std::string &name)
	{
		m_name = name;
		canDelete = true;
	}

	void BaseProperty::setName(const std::string &name)
	{
		m_name = name;
	}
}
