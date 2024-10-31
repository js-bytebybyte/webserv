#include "../../includes/ConfigFile/ConfigCgi.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigCgi::ConfigCgi(void) : authorized(false), extension("")
{
}

ConfigCgi::ConfigCgi(const ConfigCgi &other)
{
	*this = other;
}

ConfigCgi &ConfigCgi::operator=(const ConfigCgi &other)
{
	if (this != &other)
	{
		authorized = other.authorized;
		extension = other.extension;
	}
	return (*this);
}

ConfigCgi::~ConfigCgi(void)
{
}

/* Getters */
bool ConfigCgi::getAuthorized(void) const
{
	return (authorized);
}

std::string ConfigCgi::getExtension(void) const
{
	return (extension);
}

/* Setters */
void ConfigCgi::setAuthorized(const bool &authorized)
{
	this->authorized = authorized;
}

void ConfigCgi::setExtension(const std::string &extension)
{
	this->extension = extension;
}
