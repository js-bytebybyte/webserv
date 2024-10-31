#pragma once

#include "../../Project.hpp"
#include "ConfigParsing.hpp"

class ConfigPreParsing : public ConfigParsing
{
  private:
	/*
		Helper functions
	*/
	bool handleErrors(void) const;

  public:
	/* Cannonical form*/
	ConfigPreParsing(void);
	ConfigPreParsing(const ConfigPreParsing &other);
	ConfigPreParsing &operator=(const ConfigPreParsing &other);
	virtual ~ConfigPreParsing(void);

	/*
		Function to parse the configuration file
	*/
	bool parse(HttpConfig &config, const bool beginPart);
};