#pragma once

#include "../../Http/HttpConfig.hpp"
#include "../../Project.hpp"
#include "../../Validator/ConfigValidator.hpp"

class ConfigParsing
{
  public:
	/* Cannonical form*/
	ConfigParsing(void);
	ConfigParsing(const ConfigParsing &other);
	ConfigParsing &operator=(const ConfigParsing &other);
	virtual ~ConfigParsing(void);

	/*
		Function to parse the configuration file
	*/
	virtual bool parse(HttpConfig &config, const bool beginPart) = 0;

	/*
		Function to print an error message
	*/
	void printError(const std::string &message) const;

	/*
		Object to validate the configuration file
	*/
	ConfigValidator configValidator;

  protected:
	/*
		Function to split a string by a delimiter this one is assinged by limit
	*/
	std::vector<std::string> split(const std::string &str, char limit) const;

	/*
		Function to skip a number of lines
	*/
	std::string skipLines(std::istringstream &stream, const int numLines);
};