#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerListenValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool listenSymbol;
	bool listenHost;
	bool listenPort;
	std::string listenIP;
	int listenPortNumber;

	/*
		Helper functions to validate the "listen" directive
	*/
	bool validateListen(const std::string &line);
	bool validateIP(std::string &ip);
	bool validatePort(const int &port);

  public:
	/* Cannonical form */
	ConfigFileServerListenValidation(void);
	ConfigFileServerListenValidation(const ConfigFileServerListenValidation &other);
	ConfigFileServerListenValidation &operator=(const ConfigFileServerListenValidation &other);
	~ConfigFileServerListenValidation(void);

	/*
		Function to validate the "listen" directive,
			including IP address and port
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getListenSymbol(void) const;
	bool getListenPort(void) const;
	bool getListenHost(void) const;
	std::string getListenIP(void) const;
	int getListenPortNumber(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};