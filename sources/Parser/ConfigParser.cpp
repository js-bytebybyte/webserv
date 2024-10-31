#include "../../includes/Parser/ConfigParser.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigParser::ConfigParser(void) : configFiller(), configPreParsing(), configFileBlockParsing(), configFileServerParsing(),
	configFileRouteParsing(), configFinalParsing()
{
}

ConfigParser::ConfigParser(const ConfigParser &other)
{
	*this = other;
}

ConfigParser &ConfigParser::operator=(const ConfigParser &other)
{
	if (this != &other)
	{
		configFiller = other.configFiller;
		configPreParsing = other.configPreParsing;
		configFileBlockParsing = other.configFileBlockParsing;
		configFileServerParsing = other.configFileServerParsing;
		configFileRouteParsing = other.configFileRouteParsing;
		configFinalParsing = other.configFinalParsing;
	}
	return (*this);
}

ConfigParser::~ConfigParser(void)
{
}

/*
	Function to parse the entire configuration file
*/
bool ConfigParser::parseConfig(HttpConfig &config)
{
	int	serverAmount;
	int	routeAmount;

	// parse the conifgfile and see if it is worth parsing the content
	if (!configPreParsing.parse(config, true))
		return (printError(INVALIDCONF), false);
	// parse the begin of a configfile
	if (!configFileBlockParsing.parse(config, true))
		return (printError(INVALIDCONF), false);
	// parse the server block
	serverAmount = prepareServer(config);
	for (int server = 0; server < serverAmount; server++)
	{
		// parse the begin of a server block
		if (!configFileServerParsing.parse(config, true))
			return (printError(INVALIDCONF), false);
		// parse the route block
		routeAmount = prepareRoute(server);
		for (int route = 0; route < routeAmount; route++)
		{
			if (!configFileRouteParsing.parse(config, true))
				return (printError(INVALIDCONF), false);
			resetRouteValues(server, route);
		}
		// parse the end of a server block
		if (!configFileServerParsing.parse(config, false))
			return (printError(INVALIDCONF), false);
		resetServer();
	}
	// parse the end of a configfile
	if (!configFileBlockParsing.parse(config, false))
		return (printError(INVALIDCONF), false);
	// parse the last elemnts and make sure the config file is valid
	if (!configFinalParsing.parse(configFiller.getConfig(), true))
		return (printError(INVALIDCONF), false);
	return (configFiller.fillConfig(config), true);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ConfigParser::printError(const std::string &message) const
{
	std::cout << TRED << "Error: " << message << TRESET << std::endl;
}

void ConfigParser::resetRouteValues(const size_t &server, const size_t &route)
{
	configFiller.fillRouteValues(server, route, configFileRouteParsing);
	configFileRouteParsing.configValidator.configFileRouteValidation.reset();
	configFileServerParsing.configValidator = configFileRouteParsing.configValidator;
}

void ConfigParser::resetServer(void)
{
	configFileServerParsing.configValidator.configFileServerValidation.reset();
	configFileBlockParsing.configValidator = configFileServerParsing.configValidator;
}

int ConfigParser::prepareServer(HttpConfig &config)
{
	configFileServerParsing.configValidator = configFileBlockParsing.configValidator;
	configFiller.fillConfigValues(config, configFileBlockParsing);
	return (configFileBlockParsing.configValidator.configFileBlockValidation.getExpectedServers());
}

int ConfigParser::prepareRoute(const size_t &server)
{
	configFileServerParsing.configValidator.configFileRouteValidation.setSeenRoutes(0);
	configFileRouteParsing.configValidator = configFileServerParsing.configValidator;
	configFiller.fillServerValues(server, configFileServerParsing);
	configFileRouteParsing.configValidator.configFileRouteValidation.setSeenLines(0);
	return (configFileServerParsing.configValidator.configFileServerValidation.route.getExpectedRoutes());
}
