#include "../../../includes/Parsing/Config/ConfigPreParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigPreParsing::ConfigPreParsing(void)
{
}

ConfigPreParsing::ConfigPreParsing(const ConfigPreParsing &other) : ConfigParsing(other)
{
	*this = other;
}

ConfigPreParsing &ConfigPreParsing::operator=(const ConfigPreParsing &other)
{
	(void)other;
	return (*this);
}

ConfigPreParsing::~ConfigPreParsing(void)
{
}

/*
	Function to parse the configuration file
*/
bool ConfigPreParsing::parse(HttpConfig &config, const bool beginPart)
{
	(void)beginPart;
	std::string filePath = config.filePath.getPath();
	configValidator.configPreValidation.isValidConfigFile(filePath);
	if (handleErrors() == false)
		return (false);
	return (true);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigPreParsing::handleErrors(void) const
{
	ConfigPreValidation validator = configValidator.configPreValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.getReadable(), NOFILE),
		std::make_pair(validator.getFile(), DIRFILE),
		std::make_pair(validator.getFormat(), CONFIGFILE),
		std::make_pair(validator.getValid(), INVALIDCONF)};
	// get the size of the array
	int size = sizeof(error) / sizeof(error[0]);
	// loop through the array to check if there is any error
	for (int i = 0; i < size; i++)
	{
		if (error[i].first == false)
		{
			printError(error[i].second);
			return (false);
		}
	}
	return (true);
}
