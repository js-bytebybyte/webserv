#include "../../../includes/Parsing/Config/ConfigFileBlockParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileBlockParsing::ConfigFileBlockParsing(void)
{
}

ConfigFileBlockParsing::ConfigFileBlockParsing(const ConfigFileBlockParsing &other) : ConfigFileParsing(other)
{
	*this = other;
}

ConfigFileBlockParsing &ConfigFileBlockParsing::operator=(const ConfigFileBlockParsing &other)
{
	(void)other;
	return (*this);
}

ConfigFileBlockParsing::~ConfigFileBlockParsing(void)
{
}

/*
	function to parse the configuration file header and footer
*/
bool ConfigFileBlockParsing::parse(HttpConfig &config, const bool beginPart)
{
	if (beginPart)
		return (parseBeginBlock(config));
	else
		return (parseEndBlock(config));
}

bool ConfigFileBlockParsing::parseBeginBlock(HttpConfig &config)
{
	int	seenLines;

	std::istringstream file(readFile(config.filePath.getPath()));
	config.setFileContent(file);
	configValidator.configFileBlockValidation.validateBeginBlock(config);
	if (handleBeginBlockErrors() == false)
		return (false);
	// update the to parse elements
	seenLines = configValidator.configFileBlockValidation.getSeenLines();
	std::istringstream newF(skipLines(file, seenLines));
	config.setFileContent(newF);
	return (true);
}

bool ConfigFileBlockParsing::parseEndBlock(HttpConfig &config)
{
	int	seenLines;

	configValidator.configFileBlockValidation.validateEndBlock(config);
	std::istringstream file(config.getFileContent().str());
	if (handleEndBlockErrors() == false)
		return (false);
	// update the to parse elements
	seenLines = configValidator.configFileBlockValidation.getSeenLines();
	std::istringstream newF(skipLines(file, seenLines));
	config.setFileContent(newF);
	return (true);
}

/*PRIVATE FUNCTIONS*/
bool ConfigFileBlockParsing::handleBeginBlockErrors(void) const
{
	ConfigFileBlockValidation validator = configValidator.configFileBlockValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.getValidConfigHeader(), CONFIGHEAD),
		std::make_pair(validator.getServerAmountSymbol(), CONFIGSYMBOL),
		std::make_pair(validator.getServerAmout(), CONFIGAMOUNT)};
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

bool ConfigFileBlockParsing::handleEndBlockErrors(void) const
{
	ConfigFileBlockValidation validator = configValidator.configFileBlockValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.getMatchingServers(), CONFIGFOOTER),
		std::make_pair(validator.getValidConfig(), CONFIGTAIL)};
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
