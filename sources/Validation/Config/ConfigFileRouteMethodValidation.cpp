#include "../../../includes/Validation/Config/ConfigFileRouteMethodValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteMethodValidation::ConfigFileRouteMethodValidation(void) : methodSymbol(false), method(false), methods()
{
}

ConfigFileRouteMethodValidation::ConfigFileRouteMethodValidation(const ConfigFileRouteMethodValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteMethodValidation &ConfigFileRouteMethodValidation::operator=(const ConfigFileRouteMethodValidation &other)
{
	if (this != &other)
	{
		methodSymbol = other.methodSymbol;
		method = other.method;
		methods = other.methods;
	}
	return (*this);
}

ConfigFileRouteMethodValidation::~ConfigFileRouteMethodValidation(void)
{
}

/*
	Function to validate the "method" directive
*/
bool ConfigFileRouteMethodValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateMethod(line))
		return (false);
	if (!validateMethodValue(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteMethodValidation::getMethodSymbol(void) const
{
	return (methodSymbol);
}

bool ConfigFileRouteMethodValidation::getMethod(void) const
{
	return (method);
}

std::vector<std::string> ConfigFileRouteMethodValidation::getMethods(void) const
{
	return (methods);
}

/*Helper functions*/
void ConfigFileRouteMethodValidation::reset(void)
{
	methodSymbol = false;
	method = false;
	methods.clear();
}
/*PRIVATE FUNCTIONS*/
bool ConfigFileRouteMethodValidation::validateMethod(std::string &line)
{
	if (strncmp(line.c_str(), METHODKEY, strlen(METHODKEY)) != 0)
		return (false);
	methodSymbol = true;
	return (true);
}

bool ConfigFileRouteMethodValidation::validateMethodValue(std::string &line)
{
	int	size;

	if (line.empty())
		return (false);
	line = line.substr(strlen(METHODKEY));
	std::vector<std::string> methodArgs = split(line, ' ');
	if (methodArgs.back() != DELIMITTER)
		return (false);
	methodArgs.pop_back(); // Remove ";" for further validation
	std::string methodsArg = methodArgs[0];
	// check if we will allow it
	if (methodsArg == NOBODY)
	{
		method = true;
		return (true);
	}
	size = methodsArg.size();
	if (methodsArg.empty() || methodsArg[0] != BEGINARRAY || methodsArg[size - 1] != ENDARRAY)
		return (false);
	std::string onlyMethods = methodsArg.substr(1, methodsArg.size() - 2);
	std::vector<std::string> methodList = split(onlyMethods, ',');
	std::vector<std::string> allowedMethods;
	std::string methodsArray[] = {GETKEY, POSTKEY, DELETEKEY};
	allowedMethods.insert(allowedMethods.end(), methodsArray, methodsArray + 3);
	for (size_t i = 0; i < methodList.size(); i++)
	{
		if (std::count(allowedMethods.begin(), allowedMethods.end(), methodList[i]) == 0)
			return (false);
	}
	method = true;
	methods = methodList;
	return (true);
}
