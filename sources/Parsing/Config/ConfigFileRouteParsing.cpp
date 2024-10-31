#include "../../../includes/Parsing/Config/ConfigFileRouteParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileRouteParsing::ConfigFileRouteParsing(void)
{
}

ConfigFileRouteParsing::ConfigFileRouteParsing(const ConfigFileRouteParsing &other) : ConfigFileParsing(other)
{
	*this = other;
}

ConfigFileRouteParsing &ConfigFileRouteParsing::operator=(const ConfigFileRouteParsing &other)
{
	(void)other;
	return (*this);
}

ConfigFileRouteParsing::~ConfigFileRouteParsing(void)
{
}

/*
	Function to parse the configuration file
*/

bool ConfigFileRouteParsing::parse(HttpConfig &config, const bool beginPart)
{
	if (beginPart)
		return (parseBeginBlock(config));
	else
		return (parseEndBlock(config));
}

bool ConfigFileRouteParsing::parseBeginBlock(HttpConfig &config)
{
	int	seenLines;
	int	prevSeenLines;
	int	newSeenLines;
	int	routes;

	std::istringstream file(config.getFileContent().str());
	configValidator.configFileRouteValidation.validateRouteBlock(config);
	if (handleBeginBlockErrors() == false)
		return (false);
	if (handleEndBlockErrors() == false)
		return (false);
	// Update the seen lines and the file content that needs to be parsed
	seenLines = configValidator.configFileRouteValidation.getSeenLines();
	prevSeenLines = configValidator.configFileBlockValidation.getSeenLines();
	newSeenLines = seenLines + prevSeenLines;
	configValidator.configFileBlockValidation.setSeenLines(newSeenLines);
	std::istringstream newF(skipLines(file, seenLines));
	config.setFileContent(newF);
	routes = configValidator.configFileRouteValidation.getSeenRoutes();
	configValidator.configFileServerValidation.setSeenRoutes(routes);
	return (true);
}

bool ConfigFileRouteParsing::parseEndBlock(HttpConfig &config)
{
	(void)config;
	return (true);
}

/*PRIVATE FUNCTIONS*/
bool ConfigFileRouteParsing::handleBeginBlockErrors(void) const
{
	ConfigFileRouteValidation validator = configValidator.configFileRouteValidation;
	// create a pair with the chceck and the corresponding error message
	std::pair<bool, std::string> errors[] = {
		std::make_pair(validator.route.getRouteSymbol(), ROUTE),
		std::make_pair(validator.route.getRoute(), ROUTEVALUE),
		std::make_pair(validator.method.getMethodSymbol(), METHOD),
		std::make_pair(validator.method.getMethod(), METHODVALUE),
		std::make_pair(validator.redirect.getRedirectSymbol(), REDIRECT),
		std::make_pair(validator.redirect.getRedirect(), REDIRECTVALUE),
		std::make_pair(validator.entry.getEntrySymbol(), ENTRYSYMBOLROUTE),
		std::make_pair(validator.entry.getEntry(), ENTRYROUTE),
		std::make_pair(validator.tree.getTreeSymbol(), TREE),
		std::make_pair(validator.tree.getTree(), TREEVALUE),
		std::make_pair(validator.index.getIndexSymbol(), DEFAULTPAGE),
		std::make_pair(validator.index.getIndex(), DEFAULTPAGEVALUE),
		std::make_pair(validator.upload.getUploadSymbol(), UPLOAD),
		std::make_pair(validator.upload.getUpload(), UPLOADVALUE),
		std::make_pair(validator.cgi.getCgiSymbol(), CGIELEMENT),
		std::make_pair(validator.cgi.getCgiPermission(), CGIPERMISSIONS),
		std::make_pair(validator.cgi.getCgiExtension(), CGIUSE)};
	// get the size of the array
	int size = sizeof(errors) / sizeof(errors[0]);
	// loop through the array to check if there is any error
	for (int i = 0; i < size; i++)
	{
		if (errors[i].first == false)
		{
			printError(errors[i].second);
			return (false);
		}
	}
	return (true);
}

bool ConfigFileRouteParsing::handleEndBlockErrors(void) const
{
	ConfigFileRouteValidation validator = configValidator.configFileRouteValidation;

	if (validator.getValidRoute() == false)
		return (printError(ROUTETAIL), false);
	return (true);
}
