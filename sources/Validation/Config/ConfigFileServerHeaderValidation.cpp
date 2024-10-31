#include "../../../includes/Validation/Config/ConfigFileServerHeaderValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerHeaderValidation::ConfigFileServerHeaderValidation(void) : header(false), seenServers(0)
{
}

ConfigFileServerHeaderValidation::ConfigFileServerHeaderValidation(const ConfigFileServerHeaderValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerHeaderValidation &ConfigFileServerHeaderValidation::operator=(const ConfigFileServerHeaderValidation &other)
{
	if (this != &other)
	{
		header = other.header;
		seenServers = other.seenServers;
	}
	return (*this);
}

ConfigFileServerHeaderValidation::~ConfigFileServerHeaderValidation(void)
{
}

/*
	Function to validate the "header" directive
*/
bool ConfigFileServerHeaderValidation::validate(std::istringstream &file, std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateHeader(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileServerHeaderValidation::getHeader(void) const
{
	return (header);
}

int ConfigFileServerHeaderValidation::getSeenServers(void) const
{
	return (seenServers);
}

/*
	Function to reset the object
*/
void ConfigFileServerHeaderValidation::reset(void)
{
	header = false;
	seenServers = 0;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileServerHeaderValidation::validateHeader(const std::string &line)
{
	if (std::strcmp(line.c_str(), BEGINSERVER) != 0)
		return (false);
	header = true;
	seenServers++;
	return (true);
}
