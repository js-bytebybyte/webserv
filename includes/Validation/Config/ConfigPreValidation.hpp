#pragma once

#include "../../Project.hpp"

class ConfigPreValidation
{
  private:
	/* Private variables */
	bool valid;
	bool format;
	bool file;
	bool readable;

	/*
		Helper functions
	*/
	bool isValidFormat(const std::string &config) const;
	bool isDirectory(const std::string &config) const;
	bool isReadable(const std::string &config) const;

  public:
	/* Cannonical form*/
	ConfigPreValidation(void);
	ConfigPreValidation(const ConfigPreValidation &other);
	ConfigPreValidation &operator=(const ConfigPreValidation &other);
	~ConfigPreValidation(void);

	/*
		Function that will validate the ConfigPreParsing object
	*/
	void isValidConfigFile(std::string &configFile);

	/*Getters*/
	bool getValid(void) const;
	bool getFormat(void) const;
	bool getFile(void) const;
	bool getReadable(void) const;
};