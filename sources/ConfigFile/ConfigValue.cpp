#include "../../includes/ConfigFile/ConfigValue.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form */
ConfigValue::ConfigValue(void) : amount(0)
{
}

ConfigValue::ConfigValue(int value) : amount(value)
{
}

ConfigValue::ConfigValue(const ConfigValue &other)
{
	*this = other;
}

ConfigValue &ConfigValue::operator=(const ConfigValue &other)
{
	if (this != &other)
		amount = other.amount;
	return (*this);
}

ConfigValue::~ConfigValue(void)
{
}

/* Getters */
int ConfigValue::getValue(void) const
{
	return (amount);
}

/* Setters */
void ConfigValue::setValue(const int &value)
{
	amount = value;
}
