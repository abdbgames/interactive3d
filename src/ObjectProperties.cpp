#include "ObjectProperties.h"

namespace kg
{
	BaseProperty::BaseProperty(const std::string &name)
	{
		m_name = name;
	}

	void BaseProperty::setName(const std::string &name)
	{
		m_name = name;
	}
}
