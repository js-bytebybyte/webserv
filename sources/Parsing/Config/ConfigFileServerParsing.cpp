#include "../../../includes/Parsing/Config/ConfigFileServerParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileServerParsing::ConfigFileServerParsing(void)
{
}

ConfigFileServerParsing::ConfigFileServerParsing(const ConfigFileServerParsing &other) : ConfigFileParsing(other)
{
	*this = other;
}

ConfigFileServerParsing &ConfigFileServerParsing::operator=(const ConfigFileServerParsing &other)
{
	(void)other;
	return (*this);
}

ConfigFileServerParsing::~ConfigFileServerParsing(void)
{
}

/*
	Function to parse the configuration file server part
*/
bool ConfigFileServerParsing::parse(HttpConfig &config, const bool beginPart)
{
	if (beginPart)
		return (parseBeginBlock(config));
	else
		return (parseEndBlock(config));
}

bool ConfigFileServerParsing::parseBeginBlock(HttpConfig &config)
{
	int	seenLines;
	int	prevSeenLines;
	int	newSeenLines;

	std::istringstream file(config.getFileContent().str());
	configValidator.configFileServerValidation.validateBeginBlock(config);
	if (handleBeginBlockErrors() == false)
		return (false);
	// Update the seen lines and the file content that needs to be parsed
	seenLines = configValidator.configFileServerValidation.getSeenLines();
	prevSeenLines = configValidator.configFileBlockValidation.getSeenLines();
	newSeenLines = seenLines + prevSeenLines;
	configValidator.configFileBlockValidation.setSeenLines(newSeenLines);
	std::istringstream newF(skipLines(file, seenLines));
	config.setFileContent(newF);
	return (true);
}

// NEED TO DO THE VALIDATION FOR THE END BLOCK
bool ConfigFileServerParsing::parseEndBlock(HttpConfig &config)
{
	int	seenLines;
	int	prevSeenLines;
	int	newSeenLines;
	int	prevSeenServers;
	int	seenServers;
	int	newSeenServers;

	std::istringstream file(config.getFileContent().str());
	configValidator.configFileServerValidation.validateEndBlock(config);
	if (handleEndBlockErrors() == false)
		return (false);
	seenLines = configValidator.configFileServerValidation.getSeenLines();
	prevSeenLines = configValidator.configFileBlockValidation.getSeenLines();
	newSeenLines = seenLines + prevSeenLines;
	configValidator.configFileBlockValidation.setSeenLines(newSeenLines);
	seenServers = configValidator.configFileServerValidation.header.getSeenServers();
	prevSeenServers = configValidator.configFileBlockValidation.getSeenServers();
	newSeenServers = seenServers + prevSeenServers;
	configValidator.configFileBlockValidation.setSeenServers(newSeenServers);
	std::istringstream newF(skipLines(file, seenLines));
	config.setFileContent(newF);
	return (true);
}

/*PRIVATE FUNCTIONS*/

bool ConfigFileServerParsing::handleBeginBlockErrors(void) const
{
	// create a pair with the chceck and the corresponding error message
	ConfigFileServerValidation validator = configValidator.configFileServerValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.header.getHeader(), SERVERHEAD),
		std::make_pair(validator.listen.getListenSymbol(), LISTENSYMBOL),
		std::make_pair(validator.listen.getListenHost(), LISTENIP),
		std::make_pair(validator.listen.getListenPort(), LISTENPORT),
		std::make_pair(validator.domain.getDomainSymbol(), DOMAINSSYMBOL),
		std::make_pair(validator.domain.getDomain(), DOMAINS),
		std::make_pair(validator.entry.getEntrySymbol(), ENTRYSYMBOL),
		std::make_pair(validator.entry.getEntry(), ENTRY),
		std::make_pair(validator.error.getErrorsAmountSymbol(), ERRORSAMOUNTSYMBOL),
		std::make_pair(validator.error.getErrorsAmount(), ERRORSAMOUNT),
		std::make_pair(validator.error.getErrorsSymbol(), ERRORSSYMBOL),
		std::make_pair(validator.error.getErrors(), ERRORS),
		std::make_pair(validator.bodySize.getBodySizeSymbol(), BODYSYMBOL),
		std::make_pair(validator.bodySize.getBodySize(), BODYSIZE),
		std::make_pair(validator.route.getRoutesSymbol(), ROUTESYMBOL),
		std::make_pair(validator.route.getRoutes(), ROUTES)};
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

bool ConfigFileServerParsing::handleEndBlockErrors(void) const
{
	ConfigFileServerValidation validator = configValidator.configFileServerValidation;
	std::pair<bool, std::string> error[] = {
		std::make_pair(validator.getMatchingRoutes(), ROUTEMATCH),
		std::make_pair(validator.getValidServer(), SERVERTAIL)};
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
