#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerHeaderValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool header;
	int seenServers;

	/*Helper functions*/
	bool validateHeader(const std::string &line);

  public:
	ConfigFileServerHeaderValidation(void);
	ConfigFileServerHeaderValidation(const ConfigFileServerHeaderValidation &other);
	ConfigFileServerHeaderValidation &operator=(const ConfigFileServerHeaderValidation &other);
	~ConfigFileServerHeaderValidation(void);

	/*
		Function to validate the "header" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getHeader(void) const;
	int getSeenServers(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};