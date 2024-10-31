#include "../../includes/ConfigFile/ConfigListen.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigListen::ConfigListen(void) : listenHostPath(), listenPortValue()
{
}

ConfigListen::ConfigListen(ConfigPath listenHostPath, ConfigValue listenPortValue) : listenHostPath(listenHostPath), listenPortValue(listenPortValue)
{
}

ConfigListen::ConfigListen(const ConfigListen &other)
{
	*this = other;
}

ConfigListen &ConfigListen::operator=(const ConfigListen &other)
{
	if (this != &other)
	{
		listenHostPath = other.listenHostPath;
		listenPortValue = other.listenPortValue;
	}
	return (*this);
}

ConfigListen::~ConfigListen(void)
{
}
