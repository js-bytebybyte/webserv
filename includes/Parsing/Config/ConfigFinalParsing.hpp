#pragma once

#include "../../Project.hpp"
#include "ConfigParsing.hpp"

class ConfigFinalParsing : public ConfigParsing
{
  private:
	/*
		Helper functions
	*/
	bool handleErrors(void) const;

  public:
	/* Cannonical form*/
	ConfigFinalParsing(void);
	ConfigFinalParsing(const ConfigFinalParsing &other);
	ConfigFinalParsing &operator=(const ConfigFinalParsing &other);
	~ConfigFinalParsing(void);

	/*
		Function to parse the configuration file
	*/
	bool parse(HttpConfig &config, const bool beginPart);
};