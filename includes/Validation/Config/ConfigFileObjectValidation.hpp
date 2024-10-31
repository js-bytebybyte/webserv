#pragma once

#include "../../Project.hpp"

class ConfigFileObjectValidation
{
  public:
	/* Cannonical form */
	ConfigFileObjectValidation(void);
	ConfigFileObjectValidation(const ConfigFileObjectValidation &other);
	ConfigFileObjectValidation &operator=(const ConfigFileObjectValidation &other);
	virtual ~ConfigFileObjectValidation(void);

	/*
		Function to validate the "domains" directive
	*/
	virtual bool validate(std::istringstream &file, std::string &line) = 0;

  protected:
	/*
		Function to split a string by a delimiter this one is assigned by limit
	*/
	std::vector<std::string> split(const std::string &str, char limit) const;
};