#pragma once

#include "../../Project.hpp"
#include "ConfigFileParsing.hpp"

class ConfigFileBlockParsing : public ConfigFileParsing
{
  private:
	/*
		Helper functions
	*/
	bool handleBeginBlockErrors(void) const;
	bool handleEndBlockErrors(void) const;

  public:
	/* Cannonical form*/
	ConfigFileBlockParsing(void);
	ConfigFileBlockParsing(const ConfigFileBlockParsing &other);
	ConfigFileBlockParsing &operator=(const ConfigFileBlockParsing &other);
	virtual ~ConfigFileBlockParsing(void);

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