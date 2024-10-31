#include "../../includes/ConfigFile/ConfigTree.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form */
ConfigTree::ConfigTree(void) : autoindex(false)
{
}

ConfigTree::ConfigTree(bool autoindex) : autoindex(autoindex)
{
}

ConfigTree::ConfigTree(const ConfigTree &other)
{
	*this = other;
}

ConfigTree &ConfigTree::operator=(const ConfigTree &other)
{
	if (this != &other)
		autoindex = other.autoindex;
	return (*this);
}

ConfigTree::~ConfigTree(void)
{
}

/* Getters */
bool ConfigTree::getAutoindex(void) const
{
	return (autoindex);
}

/* Setters */
void ConfigTree::setAutoindex(const bool &indexation)
{
	autoindex = indexation;
}
