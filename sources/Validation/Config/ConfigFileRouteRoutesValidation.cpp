#include "../../../includes/Validation/Config/ConfigFileRouteRoutesValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteRoutesValidation::ConfigFileRouteRoutesValidation(void) : routeSymbol(false), route(false), routeValue("")
{
}

ConfigFileRouteRoutesValidation::ConfigFileRouteRoutesValidation(const ConfigFileRouteRoutesValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteRoutesValidation &ConfigFileRouteRoutesValidation::operator=(const ConfigFileRouteRoutesValidation &other)
{
	if (this != &other)
	{
		routeSymbol = other.routeSymbol;
		route = other.route;
		routeValue = other.routeValue;
	}
	return (*this);
}

ConfigFileRouteRoutesValidation::~ConfigFileRouteRoutesValidation(void)
{
}

/*
	Function to validate the route directive file
*/
bool ConfigFileRouteRoutesValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateRoute(line))
		return (false);
	if (!validateRouteValue(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteRoutesValidation::getRouteSymbol(void) const
{
	return (routeSymbol);
}

bool ConfigFileRouteRoutesValidation::getRoute(void) const
{
	return (route);
}

std::string ConfigFileRouteRoutesValidation::getRouteValue(void) const
{
	return (routeValue);
}

/*Helper functions*/
void ConfigFileRouteRoutesValidation::reset(void)
{
	routeSymbol = false;
	route = false;
	routeValue = "";
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileRouteRoutesValidation::validateRoute(std::string &line)
{
	if (strncmp(line.c_str(), ROUTESKEY, strlen(ROUTESKEY)) != 0)
		return (false);
	routeSymbol = true;
	return (true);
}

bool ConfigFileRouteRoutesValidation::validateRouteValue(std::string &line)
{
	if (line.empty())
		return (false);
	line = line.substr(strlen(ROUTESKEY));
	std::vector<std::string> routeArgs = split(line, ' ');
	if (routeArgs.size() != 2)
		return (false);
	if (routeArgs[1] != DELIMITTER)
		return (false);
	if (routeArgs[0][0] != '/')
		return (false);
	route = true;
	routeValue = routeArgs[0];
	return (true);
}