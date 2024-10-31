#include "../../../includes/Validation/Config/ConfigFileRouteTreeValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteTreeValidation::ConfigFileRouteTreeValidation(void) : treeSymbol(false), tree(false), treeValue(false)
{
}

ConfigFileRouteTreeValidation::ConfigFileRouteTreeValidation(const ConfigFileRouteTreeValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteTreeValidation &ConfigFileRouteTreeValidation::operator=(const ConfigFileRouteTreeValidation &other)
{
	if (this != &other)
	{
		treeSymbol = other.treeSymbol;
		tree = other.tree;
		treeValue = other.treeValue;
	}
	return (*this);
}

ConfigFileRouteTreeValidation::~ConfigFileRouteTreeValidation(void)
{
}

/*
	Function to validate the "tree" directive
*/
bool ConfigFileRouteTreeValidation::validate(std::istringstream &file, std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateTreeSymbol(line))
		return (false);
	if (validateTreeValue(line))
		return (true);
	return (false);
}

/*Getters*/
bool ConfigFileRouteTreeValidation::getTreeSymbol(void) const
{
	return (treeSymbol);
}

bool ConfigFileRouteTreeValidation::getTree(void) const
{
	return (tree);
}

bool ConfigFileRouteTreeValidation::getTreeValue(void) const
{
	return (treeValue);
}

/*
	Function to reset the object
*/
void ConfigFileRouteTreeValidation::reset(void)
{
	treeSymbol = false;
	tree = false;
	treeValue = false;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileRouteTreeValidation::validateTreeSymbol(std::string &line)
{
	if (strncmp(line.c_str(), TREEKEY, strlen(TREEKEY)) == 0)
		return (false);
	treeSymbol = true;
	return (true);
}

bool ConfigFileRouteTreeValidation::validateTreeValue(std::string &line)
{
	int on;
	int off;

	line = line.substr(strlen(TREEKEY) + 1);
	on = (strncmp(line.c_str(), TREEON, strlen(TREEON)) == 0);
	off = (strncmp(line.c_str(), TREEOFF, strlen(TREEOFF)) == 0);
	if (on || off)
	{
		tree = true;
		if (on)
			treeValue = true;
		else
			treeValue = false;
		return (true);
	}
	return (false);
}