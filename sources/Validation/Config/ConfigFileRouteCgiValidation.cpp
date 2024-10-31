#include "../../../includes/Validation/Config/ConfigFileRouteCgiValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteCgiValidation::ConfigFileRouteCgiValidation(void) : cgiSymbol(false), cgiPermission(false), cgiExtension(false), cgiPermissionValue(false),
	cgiExtensionValue("")
{
}

ConfigFileRouteCgiValidation::ConfigFileRouteCgiValidation(const ConfigFileRouteCgiValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteCgiValidation &ConfigFileRouteCgiValidation::operator=(const ConfigFileRouteCgiValidation &other)
{
	if (this != &other)
	{
		cgiSymbol = other.cgiSymbol;
		cgiPermission = other.cgiPermission;
		cgiExtension = other.cgiExtension;
		cgiPermissionValue = other.cgiPermissionValue;
		cgiExtensionValue = other.cgiExtensionValue;
	}
	return (*this);
}

ConfigFileRouteCgiValidation::~ConfigFileRouteCgiValidation(void)
{
}

/*
	Function to validate the configuration file
*/
bool ConfigFileRouteCgiValidation::validate(std::istringstream &file, std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateCgiSymbol(line))
		return (false);
	if (!validateCgi(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteCgiValidation::getCgiSymbol(void) const
{
	return (cgiSymbol);
}

bool ConfigFileRouteCgiValidation::getCgiPermission(void) const
{
	return (cgiPermission);
}

bool ConfigFileRouteCgiValidation::getCgiExtension(void) const
{
	return (cgiExtension);
}

bool ConfigFileRouteCgiValidation::getCgiPermissionValue(void) const
{
	return (cgiPermissionValue);
}

std::string ConfigFileRouteCgiValidation::getCgiExtensionValue(void) const
{
	return (cgiExtensionValue);
}

/*
	Function to reset the object
*/
void ConfigFileRouteCgiValidation::reset(void)
{
	cgiSymbol = false;
	cgiPermission = false;
	cgiExtension = false;
	cgiPermission = false;
	cgiExtensionValue = "";
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigFileRouteCgiValidation::validateCgiSymbol(std::string &line)
{
	if (strncmp(line.c_str(), CGIKEY, strlen(CGIKEY)) != 0)
		return (false);
	cgiSymbol = true;
	return (true);
}

bool ConfigFileRouteCgiValidation::validateCgi(std::string &line)
{
	if (line.empty())
		return (false);
	line = line.substr(strlen(CGIKEY));
	std::vector<std::string> args = split(line, ' ');
	if (args.size() != 3)
		return (false);
	if (args[2] != DELIMITTER)
		return (false);
	args.pop_back();
	if (args[0].empty())
		return (false);
	if (!validateCgiPermission(args[0]))
		return (false);
	if (!validateCgiExtension(args[1]))
		return (false);
	return (true);
}

bool ConfigFileRouteCgiValidation::validateCgiPermission(std::string &permission)
{
	if (permission != CGIOK && permission != CGINOTOK)
		return (false);
	cgiPermission = true;
	if (permission == CGIOK)
		cgiPermissionValue = true;
	else
		cgiPermissionValue = false;
	return (true);
}

bool ConfigFileRouteCgiValidation::validateCgiExtension(std::string &extension)
{
	// might need to change this
	if (extension != CGIEXTENSION1 && extension != CGIEXTENSIONBONUS && extension != CGIPROHIBITED)
		return (false);
	if (cgiPermissionValue == false && extension == CGIPROHIBITED)
	{
		cgiExtensionValue = "";
		cgiExtension = true;
		return (true);
	}
	else if (cgiPermissionValue == true && (extension == CGIEXTENSION1 || extension == CGIEXTENSIONBONUS))
	{
		cgiExtensionValue = extension;
		cgiExtension = true;
		return (true);
	}
	return (false);
}
