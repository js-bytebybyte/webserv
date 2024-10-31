#pragma once

#include "../../Http/HttpConfig.hpp"
#include "../../Project.hpp"

class ConfigFinalValidation
{
  private:
	/*Privte variables*/
	bool ports;
	bool onlyTree;
	bool onlyRedirection;
	bool neitherTreeNorRedirection;
	bool choisesRoute;

	/*
		Helper functions
	*/
	bool validPorts(const HttpConfig &config);
	bool validEntryRedirectionTree(const HttpConfig &config);

  public:
	/* Cannonical form*/
	ConfigFinalValidation(void);
	ConfigFinalValidation(const ConfigFinalValidation &other);
	ConfigFinalValidation &operator=(const ConfigFinalValidation &other);
	~ConfigFinalValidation(void);

	/*Getter*/
	bool getPorts(void) const;
	bool getChoisesRoute(void) const;

	/*
		Function to validate the configuration file
	*/
	bool isValidConfigFile(const HttpConfig &config);
};