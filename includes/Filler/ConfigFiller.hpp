#pragma once

#include "../Http/HttpConfig.hpp"
#include "../Parsing/Config/ConfigFileBlockParsing.hpp"
#include "../Parsing/Config/ConfigFileRouteParsing.hpp"
#include "../Parsing/Config/ConfigFileServerParsing.hpp"
#include "../Project.hpp"

class ConfigFiller
{
  private:
	HttpConfig temp;

	/*
		Helper functions
	*/
	void fillRoute(ConfigRoute &route, const ConfigFileRouteParsing &parser);
	void fillErrorValues(const size_t &index, const ConfigFileRouteParsing &parser);
	void fillCgiValues(ConfigRoute &route, const ConfigFileRouteValidation &validator);
	std::vector<int> convert(const std::vector<std::string> &vector) const;

  public:
	/* Cannonical form*/
	ConfigFiller(void);
	ConfigFiller(const ConfigFiller &other);
	ConfigFiller &operator=(const ConfigFiller &other);
	~ConfigFiller(void);

	/*
		All the functions that are needed to fill the configuration
	*/
	void fillConfigValues(HttpConfig &config,
		const ConfigFileBlockParsing &parser);
	void fillServerValues(const size_t &server,
		const ConfigFileServerParsing &parser);
	void fillRouteValues(const size_t &server, const size_t &route, const ConfigFileRouteParsing &parser);
	void fillConfig(HttpConfig &destination);

	/*Getter*/
	HttpConfig &getConfig(void);
};