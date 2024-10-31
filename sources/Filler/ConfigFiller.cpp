#include "../../includes/Filler/ConfigFiller.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFiller::ConfigFiller(void) : temp()
{
}

ConfigFiller::ConfigFiller(const ConfigFiller &other)
{
	*this = other;
}

ConfigFiller &ConfigFiller::operator=(const ConfigFiller &other)
{
	if (this != &other)
		temp = other.temp;
	return (*this);
}

ConfigFiller::~ConfigFiller(void)
{
}

/*
	All the functions that are needed to fill the configuration
*/
void ConfigFiller::fillConfigValues(HttpConfig &config, const ConfigFileBlockParsing &parser)
{
	ConfigFileBlockValidation	validator;
	int							serverAmount;

	validator = parser.configValidator.configFileBlockValidation;
	serverAmount = validator.getExpectedServers();
	std::istringstream content("NULL");
	std::string path = config.filePath.getPath();
	// set the values
	temp.serverCount.setValue(serverAmount);
	temp.serverConfigs = std::vector<ConfigServer>(serverAmount);
	temp.setFileContent(content);
	temp.filePath.setPath(path);
}

void ConfigFiller::fillServerValues(const size_t &server, const ConfigFileServerParsing &parser)
{
	ConfigFileServerValidation	validator;
	int							domainAmount;
	int							errorAmount;
	int							routeAmount;

	validator = parser.configValidator.configFileServerValidation;
	domainAmount = validator.domain.getDomains().size();
	errorAmount = validator.getServerErrors().size();
	routeAmount = validator.route.getExpectedRoutes();
	// set the values
	temp.serverConfigs[server].domainsVector = std::vector<std::string>(domainAmount);
	temp.serverConfigs[server].errorsVector = std::vector<ConfigError>(errorAmount);
	temp.serverConfigs[server].locationsVector = std::vector<ConfigRoute>(routeAmount);
}

void ConfigFiller::fillRouteValues(const size_t &server, const size_t &route, const ConfigFileRouteParsing &parser)
{
	ConfigFileServerValidation	validator;
	int							port;
	int							bodySize;

	validator = parser.configValidator.configFileServerValidation;
	std::string path = validator.listen.getListenIP();
	port = validator.listen.getListenPortNumber();
	std::vector<std::string> domains = validator.domain.getDomains();
	std::string root = validator.entry.getEntryPoint();
	bodySize = validator.bodySize.getBodySizeValue();
	// set the values
	temp.serverConfigs[server].listen.listenHostPath.setPath(path);
	temp.serverConfigs[server].listen.listenPortValue.setValue(port);
	temp.serverConfigs[server].domainsVector = domains;
	temp.serverConfigs[server].rootPath.setPath(root);
	temp.serverConfigs[server].bodySize.setValue(bodySize);
	fillErrorValues(server, parser);
	fillRoute(temp.serverConfigs[server].locationsVector[route], parser);
}

void ConfigFiller::fillConfig(HttpConfig &destination)
{
	destination = temp;
}

/*Getter*/
HttpConfig &ConfigFiller::getConfig(void)
{
	return (temp);
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
void ConfigFiller::fillRoute(ConfigRoute &route, const ConfigFileRouteParsing &parser)
{
	ConfigFileRouteValidation	validator;
	bool						autoindex;

	validator = parser.configValidator.configFileRouteValidation;
	std::string path = validator.route.getRouteValue();
	std::string root = validator.entry.getEntryPoint();
	std::string index = validator.index.getIndexValue();
	std::string redirect = validator.redirect.getRedirectValue();
	std::vector<std::string> methods = validator.method.getMethods();
	std::string upload = validator.upload.getUploadValue();
	autoindex = validator.tree.getTreeValue();
	// set the values
	route.routePath.setPath(path);
	route.methodsVector = methods;
	route.rootPath.setPath(root);
	route.indexPath.setPath(index);
	route.tree.setAutoindex(autoindex);
	route.redirectPath.setPath(redirect);
	route.uploadPath.setPath(upload);
	fillCgiValues(route, validator);
}

void ConfigFiller::fillErrorValues(const size_t &index, const ConfigFileRouteParsing &parser)
{
	ConfigFileServerValidation	validator;
	size_t						size;

	std::string error;
	std::vector<std::string> errorValues;
	std::vector<std::pair<std::string, std::vector<std::string> > > errors;
	validator = parser.configValidator.configFileServerValidation;
	size = temp.serverConfigs[index].errorsVector.size();
	errors = validator.getServerErrors();
	for (size_t i = 0; i < size; i++)
	{
		error = errors[i].first;
		errorValues = errors[i].second;
		// set the values
		temp.serverConfigs[index].errorsVector[i].errorMessagePath.setPath(error);
		temp.serverConfigs[index].errorsVector[i].errorCodesVector = convert(errorValues);
	}
}

void ConfigFiller::fillCgiValues(ConfigRoute &route,
	const ConfigFileRouteValidation &validator)
{
	bool	authorized;

	std::string extension;
	authorized = validator.cgi.getCgiPermissionValue();
	extension = validator.cgi.getCgiExtensionValue();
	// set the values
	route.cgi.setAuthorized(authorized);
	route.cgi.setExtension(extension);
}

std::vector<int> ConfigFiller::convert(const std::vector<std::string> &vector) const
{
	std::vector<int> result;

	for (size_t i = 0; i < vector.size(); i++)
		result.push_back(atoi(vector[i].c_str()));
	return (result);
}