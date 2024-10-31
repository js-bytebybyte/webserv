#pragma once

#include "../../Http/HttpConfig.hpp"
#include "../../Project.hpp"
#include "ConfigFileEntryValidation.hpp"
#include "ConfigFileRouteCgiValidation.hpp"
#include "ConfigFileRouteIndexValidation.hpp"
#include "ConfigFileRouteMethodValidation.hpp"
#include "ConfigFileRouteRedirectValidation.hpp"
#include "ConfigFileRouteRoutesValidation.hpp"
#include "ConfigFileRouteTreeValidation.hpp"
#include "ConfigFileRouteUploadValidation.hpp"

class ConfigFileRouteValidation
{
  private:
	/*Private variables*/
	int seenLines;
	int seenRoutes;
	bool validRoute;

  public:
	/* Cannonical form */
	ConfigFileRouteValidation(void);
	ConfigFileRouteValidation(const ConfigFileRouteValidation &other);
	ConfigFileRouteValidation &operator=(const ConfigFileRouteValidation &other);
	virtual ~ConfigFileRouteValidation(void);

	/*
		Function to validate the configuration file
	*/
	void validateRouteBlock(HttpConfig &config);

	/*Getters*/
	int getSeenLines(void) const;
	int getSeenRoutes(void) const;
	bool getValidRoute(void) const;

	/*
		function to reset the object
	*/
	void reset(void);

	/*Setters*/
	void setSeenLines(const int &seenLines);
	void setSeenRoutes(const int &seenRoutes);

	/*
		object holding the information
	*/
	ConfigFileRouteRoutesValidation route;
	ConfigFileRouteMethodValidation method;
	ConfigFileRouteRedirectValidation redirect;
	ConfigFileEntryValidation entry;
	ConfigFileRouteTreeValidation tree;
	ConfigFileRouteIndexValidation index;
	ConfigFileRouteUploadValidation upload;
	ConfigFileRouteCgiValidation cgi;
};