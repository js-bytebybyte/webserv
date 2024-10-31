#include "../../../includes/Validation/Config/ConfigFinalValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFinalValidation::ConfigFinalValidation(void) : ports(false), onlyTree(false), onlyRedirection(false), neitherTreeNorRedirection(false),
	choisesRoute(false)
{
}

ConfigFinalValidation::ConfigFinalValidation(const ConfigFinalValidation &other)
{
	*this = other;
}

ConfigFinalValidation &ConfigFinalValidation::operator=(const ConfigFinalValidation &other)
{
	if (this != &other)
	{
		ports = other.ports;
		onlyTree = other.onlyTree;
		onlyRedirection = other.onlyRedirection;
		neitherTreeNorRedirection = other.neitherTreeNorRedirection;
		choisesRoute = other.choisesRoute;
	}
	return (*this);
}

ConfigFinalValidation::~ConfigFinalValidation(void)
{
}

/*Getter*/

bool ConfigFinalValidation::getPorts(void) const
{
	return (ports);
}

bool ConfigFinalValidation::getChoisesRoute(void) const
{
	return (choisesRoute);
}
/*
	Function to validate the configuration file
*/

bool ConfigFinalValidation::isValidConfigFile(const HttpConfig &config)
{
	if (validPorts(config) == false)
		return (false);
	if (validEntryRedirectionTree(config) == false)
		return (false);
	choisesRoute = true;
	return (true);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigFinalValidation::validPorts(const HttpConfig &config)
{
	int	port;

	std::set<int> portSet;
	for (size_t i = 0; i < config.serverConfigs.size(); i++)
	{
		port = config.serverConfigs[i].listen.listenPortValue.getValue();
		if (portSet.find(port) != portSet.end())
			return (false);
		portSet.insert(port);
	}
	ports = true;
	return (true);
}

bool ConfigFinalValidation::validEntryRedirectionTree(const HttpConfig &config)
{
	for (size_t i = 0; i < config.serverConfigs.size(); i++)
	{
		ConfigServer server = config.serverConfigs[i];
		for (size_t j = 0; j < server.locationsVector.size(); j++)
		{
			ConfigRoute location = server.locationsVector[j];
			bool tree = location.tree.getAutoindex();
			std::string redirection = location.redirectPath.getPath();
			std::string page = location.indexPath.getPath();
			neitherTreeNorRedirection = false;
			onlyRedirection = false;
			onlyTree = false;
			if (tree == true && redirection.empty())
				onlyTree = true;
			else if (tree == false && !redirection.empty())
				onlyRedirection = true;
			else if (tree == false && redirection.empty())
				neitherTreeNorRedirection = true;
			if (neitherTreeNorRedirection && !onlyRedirection && !onlyTree)
				continue ;
			else if (!neitherTreeNorRedirection && onlyRedirection && !onlyTree)
				continue ;
			else if (!neitherTreeNorRedirection && !onlyRedirection && onlyTree)
				continue ;
			else
				return (false);
		}
	}
	return (true);
}