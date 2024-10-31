#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteIndexValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool indexSymbol;
	bool index;
	std::string indexValue;
	std::string entry;

	/*
		Helper functions
	*/
	bool validateIndexSymbol(std::string &line);
	bool validateIndex(std::string &line);
	bool validatePath(std::string &path);

  public:
	/* Canonical form*/
	ConfigFileRouteIndexValidation(void);
	ConfigFileRouteIndexValidation(const ConfigFileRouteIndexValidation &other);
	ConfigFileRouteIndexValidation &operator=(const ConfigFileRouteIndexValidation &other);
	~ConfigFileRouteIndexValidation(void);

	/*
		Function to validate the "route" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getIndexSymbol(void) const;
	bool getIndex(void) const;
	std::string getIndexValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);

	/*Setters*/
	void setEntry(std::string entry);
};