#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteRoutesValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool routeSymbol;
	bool route;
	std::string routeValue;

	/*Helper functions*/
	bool validateRoute(std::string &line);
	bool validateRouteValue(std::string &line);

  public:
	/* Canonical form*/
	ConfigFileRouteRoutesValidation(void);
	ConfigFileRouteRoutesValidation(const ConfigFileRouteRoutesValidation &other);
	ConfigFileRouteRoutesValidation &operator=(const ConfigFileRouteRoutesValidation &other);
	~ConfigFileRouteRoutesValidation(void);

	/*
		Function to validate the "route" directive file
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getRouteSymbol(void) const;
	bool getRoute(void) const;
	std::string getRouteValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};