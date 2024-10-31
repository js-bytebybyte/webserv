#pragma once

#include "../../Project.hpp"
#include "ConfigFileParsing.hpp"

class ConfigFileServerParsing : public ConfigFileParsing
{
  private:
	/*
		Helper functions
	*/
	bool handleBeginBlockErrors(void) const;
	bool handleEndBlockErrors(void) const;

  public:
	/* Cannonical form*/
	ConfigFileServerParsing(void);
	ConfigFileServerParsing(const ConfigFileServerParsing &other);
	ConfigFileServerParsing &operator=(const ConfigFileServerParsing &other);
	virtual ~ConfigFileServerParsing(void);

	/*
		Function to parse the configuration file
	*/
	bool parse(HttpConfig &config, const bool beginPart);

	/*
		Function to parse the begin of a block
	*/
	bool parseBeginBlock(HttpConfig &config);

	/*
		Function to parse the end of a block
	*/
	bool parseEndBlock(HttpConfig &config);
};