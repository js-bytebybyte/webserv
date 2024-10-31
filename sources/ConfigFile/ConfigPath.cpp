#include "../../includes/ConfigFile/ConfigPath.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form */
ConfigPath::ConfigPath(void) : string("NULL")
{
}

ConfigPath::ConfigPath(std::string path) : string(path)
{
}

ConfigPath::ConfigPath(const ConfigPath &other)
{
	*this = other;
}

ConfigPath &ConfigPath::operator=(const ConfigPath &other)
{
	if (this != &other)
		string = other.string;
	return (*this);
}

ConfigPath::~ConfigPath(void)
{
}

/* Getters */
std::string ConfigPath::getPath(void) const
{
	return (string);
}

/* Setters */
void ConfigPath::setPath(const std::string &path)
{
	string = path;
}
