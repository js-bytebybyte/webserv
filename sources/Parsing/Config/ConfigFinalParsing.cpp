#include "../../../includes/Parsing/Config/ConfigFinalParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFinalParsing::ConfigFinalParsing(void)
{
}

ConfigFinalParsing::ConfigFinalParsing(const ConfigFinalParsing &other) : ConfigParsing(other)
{
	*this = other;
}

ConfigFinalParsing &ConfigFinalParsing::operator=(const ConfigFinalParsing &other)
{
	(void)other;
	return (*this);
}

ConfigFinalParsing::~ConfigFinalParsing(void)
{
}

/*
	Function to parse the configuration file
*/

bool ConfigFinalParsing::parse(HttpConfig &config, const bool beginPart)
{
	(void)beginPart;
	configValidator.configFinalValidation.isValidConfigFile(config);
	if (handleErrors() == false)
		return (false);
	return (true);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigFinalParsing::handleErrors(void) const
{
	ConfigFinalValidation validator = configValidator.configFinalValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.getPorts(), PORTS),
		std::make_pair(validator.getChoisesRoute(), CHOISESROUTE)};
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
