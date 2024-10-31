#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteTreeValidation : public ConfigFileObjectValidation
{
  private:
	/*Private varibales*/
	bool treeSymbol;
	bool tree;
	bool treeValue;

	/*Helper fucntions*/
	bool validateTreeSymbol(std::string &line);
	bool validateTreeValue(std::string &line);

  public:
	/* Cannonical form */
	ConfigFileRouteTreeValidation(void);
	ConfigFileRouteTreeValidation(const ConfigFileRouteTreeValidation &other);
	ConfigFileRouteTreeValidation &operator=(const ConfigFileRouteTreeValidation &other);
	~ConfigFileRouteTreeValidation(void);

	/*
		Function to validate the configuration file
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getTreeSymbol(void) const;
	bool getTree(void) const;
	bool getTreeValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};