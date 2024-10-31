#pragma once

#include "../../Http/HttpConfig.hpp"
#include "../../Project.hpp"
#include "ConfigFileEntryValidation.hpp"
#include "ConfigFileObjectValidation.hpp"
#include "ConfigFileServerBodySizeValidation.hpp"
#include "ConfigFileServerDomainValidation.hpp"
#include "ConfigFileServerErrorValidation.hpp"
#include "ConfigFileServerHeaderValidation.hpp"
#include "ConfigFileServerListenValidation.hpp"
#include "ConfigFileServerRouteValidation.hpp"

class ConfigFileServerValidation
{
  private:
	/*Private variables*/
	int seenRoutes;
	int seenLines;
	bool validServer;
	bool matchingRoutes;
	std::vector<std::pair<std::string, std::vector<std::string> > > serverErrors;

  public:
	ConfigFileServerListenValidation listen;
	ConfigFileServerDomainValidation domain;
	ConfigFileEntryValidation entry;
	ConfigFileServerBodySizeValidation bodySize;
	ConfigFileServerRouteValidation route;
	ConfigFileServerHeaderValidation header;
	ConfigFileServerErrorValidation error;

	/* Cannonical form */
	ConfigFileServerValidation(void);
	ConfigFileServerValidation(const ConfigFileServerValidation &other);
	ConfigFileServerValidation &operator=(const ConfigFileServerValidation &other);
	virtual ~ConfigFileServerValidation(void);

	/*
		Function to validate the configuration file
	*/
	void validateBeginBlock(HttpConfig &config);
	void validateEndBlock(HttpConfig &config);

	/*Getters*/
	int getSeenLines(void) const;
	bool getValidServer(void) const;
	bool getMatchingRoutes(void) const;
	int getSeenRoutes(void) const;
	std::vector<std::pair<std::string, std::vector<std::string> > > getServerErrors(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);

	/*Setters*/
	void setSeenRoutes(const int &seen);
};
