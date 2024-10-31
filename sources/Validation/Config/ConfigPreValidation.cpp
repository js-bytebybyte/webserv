#include "../../../includes/Validation/Config/ConfigPreValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigPreValidation::ConfigPreValidation(void) : valid(false), format(false), file(false), readable(false)
{
}

ConfigPreValidation::ConfigPreValidation(const ConfigPreValidation &other)
{
	*this = other;
}

ConfigPreValidation &ConfigPreValidation::operator=(const ConfigPreValidation &other)
{
	if (this != &other)
	{
		valid = other.valid;
		format = other.format;
		file = other.file;
		readable = other.readable;
	}
	return (*this);
}

ConfigPreValidation::~ConfigPreValidation(void)
{
}

/*
	Function to validate the configuration file
*/
void ConfigPreValidation::isValidConfigFile(std::string &configFile)
{
	if (!isReadable(configFile))
		return ;
	readable = true;
	if (isDirectory(configFile))
		return ;
	file = true;
	if (!isValidFormat(configFile))
		return ;
	format = true;
	if (getFormat() && getFile() && getReadable())
		valid = true;
	return ;
}

/*Getters*/
bool ConfigPreValidation::getValid(void) const
{
	return (valid);
}

bool ConfigPreValidation::getFormat(void) const
{
	return (format);
}

bool ConfigPreValidation::getFile(void) const
{
	return (file);
}

bool ConfigPreValidation::getReadable(void) const
{
	return (readable);
}

/*PRIVATE FUNCTIONS*/

/*
	Checkers for the configuration file
*/
bool ConfigPreValidation::isValidFormat(const std::string &config) const
{
	int len = config.length();
	std::string extension = EXTENSIONKEY;
	const int size = extension.length();

	if (size <= len)
	{
		const char *end = &config[len - strlen(EXTENSIONKEY)];
		if (strcmp(end, extension.c_str()) == 0)
			return (true);
	}
	return (false);
}

bool ConfigPreValidation::isDirectory(const std::string &config) const
{
	int fd = open(config.c_str(), DIRREAD);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

bool ConfigPreValidation::isReadable(const std::string &config) const
{
	int fd = open(config.c_str(), O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}