#pragma once

#include "../Handler/FileHandler.hpp"
#include "../Project.hpp"
#include "../Request/HttpRequest.hpp"
#include "ConfigError.hpp"
#include "ConfigListen.hpp"
#include "ConfigPath.hpp"
#include "ConfigRoute.hpp"
#include "ConfigValue.hpp"

class ConfigServer
{
  public:
	/* Cannonical form*/
	ConfigServer(void);
	ConfigServer(const ConfigServer &other);
	ConfigServer &operator=(const ConfigServer &other);
	~ConfigServer(void);
	void printConfig(void) const;

	/*
		objects holding the information
	*/
	ConfigListen listen;
	std::vector<std::string> domainsVector; // nom de domain
	ConfigPath rootPath;
	std::vector<ConfigError> errorsVector;
	ConfigValue bodySize;
	std::vector<ConfigRoute> locationsVector;
};