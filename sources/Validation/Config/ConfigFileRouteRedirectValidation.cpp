#include "../../../includes/Validation/Config/ConfigFileRouteRedirectValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteRedirectValidation::ConfigFileRouteRedirectValidation(void) : redirectSymbol(false), redirect(false), redirectValue("")
{
}

ConfigFileRouteRedirectValidation::ConfigFileRouteRedirectValidation(const ConfigFileRouteRedirectValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteRedirectValidation &ConfigFileRouteRedirectValidation::operator=(const ConfigFileRouteRedirectValidation &other)
{
	if (this != &other)
	{
		redirectSymbol = other.redirectSymbol;
		redirect = other.redirect;
		redirectValue = other.redirectValue;
	}
	return (*this);
}

ConfigFileRouteRedirectValidation::~ConfigFileRouteRedirectValidation(void)
{
}

/*
	Function to validate the "redirect" directive
*/
bool ConfigFileRouteRedirectValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateRedirectPrefix(line))
		return (false);
	if (!validateRedirect(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteRedirectValidation::getRedirectSymbol(void) const
{
	return (redirectSymbol);
}

bool ConfigFileRouteRedirectValidation::getRedirect(void) const
{
	return (redirect);
}

std::string ConfigFileRouteRedirectValidation::getRedirectValue(void) const
{
	return (redirectValue);
}

/*Helper functions*/
void ConfigFileRouteRedirectValidation::reset(void)
{
	redirectSymbol = false;
	redirect = false;
	redirectValue = "";
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileRouteRedirectValidation::validateRedirectPrefix(std::string &line)
{
	if (std::strncmp(line.c_str(), REDIRECTKEY, strlen(REDIRECTKEY)) != 0)
		return (false);
	redirectSymbol = true;
	return (true);
}

bool ConfigFileRouteRedirectValidation::validateRedirect(std::string &line)
{
	if (line.size() <= strlen(REDIRECTKEY))
		return (false);
	line = line.substr(strlen(REDIRECTKEY));
	if (line.empty())
		return (false);
	std::vector<std::string> redirectArgs = split(line, ' ');
	if (redirectArgs.size() != 2)
		return (false);
	if (redirectArgs[1] != DELIMITTER)
		return (false);
	redirectArgs.pop_back(); // Remove ";" for further validation
	if (redirectArgs[0].empty())
		return (false);
	if (redirectArgs[0] == NOBODY)
	{
		redirect = true;
		return (true);
	}
	redirect = true;
	redirectValue = redirectArgs[0];
	return (true);
}
