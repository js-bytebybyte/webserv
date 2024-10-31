#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerRouteValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool routesSymbol;
	bool routes;
	int expectedRoutes;

	/*Helper functions*/
	bool validateRoute(const std::string &line);
	bool validateRouteValue(const std::string &line);

  public:
	ConfigFileServerRouteValidation(void);
	ConfigFileServerRouteValidation(const ConfigFileServerRouteValidation &other);
	ConfigFileServerRouteValidation &operator=(const ConfigFileServerRouteValidation &other);
	~ConfigFileServerRouteValidation(void);

	/*
		Function to validate the "routes" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getRoutesSymbol(void) const;
	bool getRoutes(void) const;
	int getExpectedRoutes(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};