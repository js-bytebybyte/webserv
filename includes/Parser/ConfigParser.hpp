#pragma once

#include "../../includes/Http/HttpConfig.hpp"
#include "../Filler/ConfigFiller.hpp"
#include "../Http/HttpConfig.hpp"
#include "../Parsing/Config/ConfigFileBlockParsing.hpp"
#include "../Parsing/Config/ConfigFileRouteParsing.hpp"
#include "../Parsing/Config/ConfigFileServerParsing.hpp"
#include "../Parsing/Config/ConfigFinalParsing.hpp"
#include "../Parsing/Config/ConfigPreParsing.hpp"
#include "../Project.hpp"

class ConfigParser
{
  private:
	/*
		All the components that are needed to parse the request
	*/
	ConfigFiller configFiller;
	ConfigPreParsing configPreParsing;
	ConfigFileBlockParsing configFileBlockParsing;
	ConfigFileServerParsing configFileServerParsing;
	ConfigFileRouteParsing configFileRouteParsing;
	ConfigFinalParsing configFinalParsing;

	/*
		Helper functions
	*/
	void printError(const std::string &message) const;
	void resetRouteValues(const size_t &server, const size_t &route);
	void resetServer(void);
	int prepareServer(HttpConfig &config);
	int prepareRoute(const size_t &server);

  public:
	/* Cannonical form*/
	ConfigParser(void);
	ConfigParser(const ConfigParser &other);
	ConfigParser &operator=(const ConfigParser &other);
	~ConfigParser(void);

	/*
		Function to parse the entire configuration file
	*/
	bool parseConfig(HttpConfig &config);
};