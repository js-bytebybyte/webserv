#pragma once

#include "../Project.hpp"
#include "ConfigPath.hpp"

class ConfigError
{
  public:
	/* Cannonical form*/
	ConfigError(void);
	ConfigError(ConfigPath errorMessage, std::vector<int> errorCodes);
	ConfigError(const ConfigError &other);
	ConfigError &operator=(const ConfigError &other);
	~ConfigError(void);

	/*
		objects holding the information
	*/
	ConfigPath errorMessagePath;
	std::vector<int> errorCodesVector;
};