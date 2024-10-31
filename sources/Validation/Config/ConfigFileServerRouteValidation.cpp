#include "../../../includes/Validation/Config/ConfigFileServerRouteValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerRouteValidation::ConfigFileServerRouteValidation(void) : routesSymbol(false), routes(false), expectedRoutes(0)
{
}

ConfigFileServerRouteValidation::ConfigFileServerRouteValidation(const ConfigFileServerRouteValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerRouteValidation &ConfigFileServerRouteValidation::operator=(const ConfigFileServerRouteValidation &other)
{
	if (this != &other)
	{
		routesSymbol = other.routesSymbol;
		routes = other.routes;
		expectedRoutes = other.expectedRoutes;
	}
	return (*this);
}

ConfigFileServerRouteValidation::~ConfigFileServerRouteValidation(void)
{
}

/*
	Function to validate the "routes" directive
*/
bool ConfigFileServerRouteValidation::validate(std::istringstream &file, std::string &line)
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
bool ConfigFileServerRouteValidation::getRoutesSymbol(void) const
{
	return (routesSymbol);
}

bool ConfigFileServerRouteValidation::getRoutes(void) const
{
	return (routes);
}

int ConfigFileServerRouteValidation::getExpectedRoutes(void) const
{
	return (expectedRoutes);
}

/*
	Function to reset the object
*/
void ConfigFileServerRouteValidation::reset(void)
{
	routesSymbol = false;
	routes = false;
	expectedRoutes = 0;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/

bool ConfigFileServerRouteValidation::validateRoute(const std::string &line)
{
	if (std::strncmp(line.c_str(), VALUEKEY, strlen(VALUEKEY)) != 0)
		return (false);
	routesSymbol = true;
	return (true);
}

bool ConfigFileServerRouteValidation::validateRouteValue(const std::string &line)
{
	if (std::sscanf(line.c_str(), VALUEPATTERN, &expectedRoutes) != 1)
		return (false);
	if (expectedRoutes < 0 || INT16_MAX < expectedRoutes)
		return (false);
	routes = true;
	return (true);
}
