#pragma once

#include "../../Project.hpp"
#include "ConfigFileParsing.hpp"

class ConfigFileRouteParsing : public ConfigFileParsing
{
  private:
	/*
		Helper functions
	*/
	bool handleBeginBlockErrors(void) const;
	bool handleEndBlockErrors(void) const;

  public:
	/* Cannonical form*/
	ConfigFileRouteParsing(void);
	ConfigFileRouteParsing(const ConfigFileRouteParsing &other);
	ConfigFileRouteParsing &operator=(const ConfigFileRouteParsing &other);
	virtual ~ConfigFileRouteParsing(void);

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