#pragma once

#include "../../Http/HttpConfig.hpp"
#include "../../Project.hpp"

class ConfigFileBlockValidation
{
  private:
	/*Private variables*/
	int seenServers;
	int expectedServers;
	int seenLines;
	bool validConfigHeader;
	bool serverAmountSymbol;
	bool serverAmout;
	bool validConfig;
	bool matchingServers;

	/*Helper functions*/
	bool validateConfigHeader(const std::string &line);
	bool validateServerAmountSymbol(const std::string &line);
	bool validateServerAmount(const std::string &line);
	bool validateMatchingServers(void);
	bool validateConfig(std::istringstream &file, std::string &line);

  public:
	/* Cannonical form*/
	ConfigFileBlockValidation(void);
	ConfigFileBlockValidation(const ConfigFileBlockValidation &other);
	ConfigFileBlockValidation &operator=(const ConfigFileBlockValidation &other);
	~ConfigFileBlockValidation(void);

	/*
		Function to validate the configuration file
	*/
	void validateBeginBlock(const HttpConfig &config);
	void validateEndBlock(const HttpConfig &config);

	/*Getters*/
	int getSeenServers(void) const;
	int getExpectedServers(void) const;
	int getSeenLines(void) const;
	bool getValidConfigHeader(void) const;
	bool getServerAmountSymbol(void) const;
	bool getServerAmout(void) const;
	bool getValidConfig(void) const;
	bool getMatchingServers(void) const;

	/*Setters*/
	void setSeenServers(const int &seenServers);
	void setSeenLines(const int &seenLines);
};