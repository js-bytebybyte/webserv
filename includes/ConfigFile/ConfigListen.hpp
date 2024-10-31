#pragma once

#include "../Project.hpp"
#include "ConfigPath.hpp"
#include "ConfigValue.hpp"

class ConfigListen
{
  public:
	/* Cannonical form*/
	ConfigListen(void);
	ConfigListen(ConfigPath listenHostPath, ConfigValue listenPortValue);
	ConfigListen(const ConfigListen &other);
	ConfigListen &operator=(const ConfigListen &other);
	~ConfigListen(void);

	/*
		objects holding the information
	*/
	ConfigPath listenHostPath;
	ConfigValue listenPortValue;
};