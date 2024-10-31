#include "../../includes/ConfigFile/ConfigRoute.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigRoute::ConfigRoute(void) : routePath(), methodsVector(), rootPath(), indexPath(),
	tree(), redirectPath(), uploadPath(), cgi()
{
}

ConfigRoute::ConfigRoute(const ConfigRoute &other)
{
	*this = other;
}

ConfigRoute &ConfigRoute::operator=(const ConfigRoute &other)
{
	if (this != &other)
	{
		routePath = other.routePath;
		methodsVector = other.methodsVector;
		rootPath = other.rootPath;
		indexPath = other.indexPath;
		tree = other.tree;
		redirectPath = other.redirectPath;
		uploadPath = other.uploadPath;
		cgi = other.cgi;
	}
	return (*this);
}

ConfigRoute::~ConfigRoute(void)
{
}
