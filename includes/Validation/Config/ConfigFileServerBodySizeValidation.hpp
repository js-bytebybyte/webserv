#pragma once

#include "../../Http/HttpConfig.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerBodySizeValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool bodySizeSymbol;
	bool bodySize;
	int bodySizeValue;

	/*Helper functions*/
	bool validateBodySize(std::string &line);
	bool validateBodySizeValue(std::string &line);

  public:
	/* Cannonical form */
	ConfigFileServerBodySizeValidation(void);
	ConfigFileServerBodySizeValidation(const ConfigFileServerBodySizeValidation &other);
	ConfigFileServerBodySizeValidation &operator=(const ConfigFileServerBodySizeValidation &other);
	~ConfigFileServerBodySizeValidation(void);

	/*
		Function to validate the "body size" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getBodySizeSymbol(void) const;
	bool getBodySize(void) const;
	int getBodySizeValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};
