#include "../../../includes/Validation/Config/ConfigFileServerBodySizeValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerBodySizeValidation::ConfigFileServerBodySizeValidation(void) : bodySizeSymbol(false), bodySize(false), bodySizeValue(0)
{
}

ConfigFileServerBodySizeValidation::ConfigFileServerBodySizeValidation(const ConfigFileServerBodySizeValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerBodySizeValidation &ConfigFileServerBodySizeValidation::operator=(const ConfigFileServerBodySizeValidation &other)
{
	if (this != &other)
	{
		bodySizeSymbol = other.bodySizeSymbol;
		bodySize = other.bodySize;
		bodySizeValue = other.bodySizeValue;
	}
	return (*this);
}

ConfigFileServerBodySizeValidation::~ConfigFileServerBodySizeValidation(void)
{
}

/*
	Function to validate the "body size" directive
*/
bool ConfigFileServerBodySizeValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateBodySize(line))
		return (false);
	if (!validateBodySizeValue(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileServerBodySizeValidation::getBodySizeSymbol(void) const
{
	return (bodySizeSymbol);
}

bool ConfigFileServerBodySizeValidation::getBodySize(void) const
{
	return (bodySize);
}

int ConfigFileServerBodySizeValidation::getBodySizeValue(void) const
{
	return (bodySizeValue);
}

/*
	Function to reset the object
*/
void ConfigFileServerBodySizeValidation::reset(void)
{
	bodySizeSymbol = false;
	bodySize = false;
	bodySizeValue = 0;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileServerBodySizeValidation::validateBodySize(std::string &line)
{
	if (std::strncmp(line.c_str(), BODYKEY, strlen(BODYKEY)) != 0)
		return (false);
	bodySizeSymbol = true;
	return (true);
}

bool ConfigFileServerBodySizeValidation::validateBodySizeValue(std::string &line)
{
	if (std::sscanf(line.c_str(), BODYPATTERN, &bodySizeValue) != 1)
		return (false);
	// use -1 to represent no limit but artificially limit it to MAX_BUF - 1
	if (bodySizeValue < -1 || MAX_BUF <= bodySizeValue)
		return (false);
	if (bodySizeValue == -1)
		bodySizeValue = MAX_BUF - 1;
	bodySize = true;
	return (true);
}
