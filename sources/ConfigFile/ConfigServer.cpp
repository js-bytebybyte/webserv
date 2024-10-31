#include "../../includes/ConfigFile/ConfigServer.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigServer::ConfigServer(void) : listen(), domainsVector(), rootPath(), errorsVector(),
	bodySize(-1), locationsVector()
{
}

ConfigServer::ConfigServer(const ConfigServer &other)
{
	*this = other;
}

ConfigServer &ConfigServer::operator=(const ConfigServer &other)
{
	if (this != &other)
	{
		listen = other.listen;
		domainsVector = other.domainsVector;
		rootPath = other.rootPath;
		errorsVector = other.errorsVector;
		bodySize = other.bodySize;
		locationsVector = other.locationsVector;
	}
	return (*this);
}

ConfigServer::~ConfigServer(void)
{
}

void ConfigServer::printConfig(void) const
{
	std::cout << "\tListen: \n";
	std::cout << "\t\tHost: " << listen.listenHostPath.getPath() << std::endl;
	std::cout << "\t\tPort: " << listen.listenPortValue.getValue() << std::endl;
	std::cout << std::endl;
	std::cout << "\tDomains: \n";
	std::cout << "\t\tdomainNames: ";
	for (size_t i = 0; i < domainsVector.size(); i++)
		std::cout << domainsVector[i] << " ";
	std::cout << std::endl << std::endl;
	std::cout << "\tRoot path: \n";
	std::cout << "\t\tpath: " << rootPath.getPath() << std::endl;
	std::cout << std::endl;
	std::cout << "\tErrors: \n";
	for (size_t i = 0; i < errorsVector.size(); i++)
	{
		std::cout << "\t\tError file: " << errorsVector[i].errorMessagePath.getPath() << std::endl;
		std::cout << "\t\tError codes: ";
		for (size_t j = 0; j < errorsVector[i].errorCodesVector.size(); j++)
			std::cout << errorsVector[i].errorCodesVector[j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "\tBody size: \n";
	std::cout << "\t\tSize: " << bodySize.getValue() << std::endl;
	std::cout << std::endl;
	std::cout << "\tLocations: \n";
	for (size_t i = 0; i < locationsVector.size(); i++)
	{
		std::cout << "\t\tURI: " << locationsVector[i].routePath.getPath() << std::endl;
		std::cout << "\t\tMethods: ";
		for (size_t j = 0; j < locationsVector[i].methodsVector.size(); j++)
			std::cout << locationsVector[i].methodsVector[j] << " ";
		std::cout << std::endl;
		std::cout << "\t\tEntry path: " << locationsVector[i].rootPath.getPath() << std::endl;
		std::cout << "\t\tIndex: " << locationsVector[i].indexPath.getPath() << std::endl;
		std::cout << "\t\tAutoindex: " << locationsVector[i].tree.getAutoindex() << std::endl;
		std::cout << "\t\tRedirect: " << locationsVector[i].redirectPath.getPath() << std::endl;
		std::cout << "\t\tUpload: " << locationsVector[i].uploadPath.getPath() << std::endl;
		std::cout << "\t\tCgi: \n";
		std::cout << "\t\t\tPermission: " << locationsVector[i].cgi.getAuthorized() << std::endl;
		std::cout << "\t\t\tExtension: " << locationsVector[i].cgi.getExtension() << std::endl;
		std::cout << std::endl;
	}
}
