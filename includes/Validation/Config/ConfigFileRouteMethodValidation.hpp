#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteMethodValidation : public ConfigFileObjectValidation
{
  private:
	/*Private functions*/
	bool methodSymbol;
	bool method;
	std::vector<std::string> methods;

	/*
		Helper functions
	*/
	bool validateMethod(std::string &line);
	bool validateMethodValue(std::string &line);

  public:
	/* Cannonical form */
	ConfigFileRouteMethodValidation(void);
	ConfigFileRouteMethodValidation(const ConfigFileRouteMethodValidation &other);
	ConfigFileRouteMethodValidation &operator=(const ConfigFileRouteMethodValidation &other);
	~ConfigFileRouteMethodValidation(void);

	/*
		Function to validate the "method" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getMethodSymbol(void) const;
	bool getMethod(void) const;
	std::vector<std::string> getMethods(void) const;

	/*Helper functions*/
	void reset(void);
};