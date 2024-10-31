#pragma once

#include "../../Project.hpp"
#include "../../Validation/Config/ConfigFileObjectValidation.hpp"
#include "ConfigParsing.hpp"

class ConfigFileParsing : public ConfigParsing
{
  public:
	/* Cannonical form*/
	ConfigFileParsing(void);
	ConfigFileParsing(const ConfigFileParsing &other);
	ConfigFileParsing &operator=(const ConfigFileParsing &other);
	virtual ~ConfigFileParsing(void);

	/*
		Function to parse the configuration file
	*/
	virtual bool parse(HttpConfig &config, const bool beginPart) = 0;

  protected:
	/*
		Function to parse to th point you encounter the next block
	*/
	virtual bool parseBeginBlock(HttpConfig &config) = 0;

	/*
		Function to parse after you are finished inside the block
	*/
	virtual bool parseEndBlock(HttpConfig &config) = 0;

	/*
		Function to read the file
	*/
	std::string readFile(const std::string &file) const;

	/*
		Helper functions
	*/
	virtual bool handleBeginBlockErrors(void) const = 0;
	virtual bool handleEndBlockErrors(void) const = 0;
};