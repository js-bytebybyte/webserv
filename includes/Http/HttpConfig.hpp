#pragma once

#include "../ConfigFile/ConfigPath.hpp"
#include "../ConfigFile/ConfigServer.hpp"
#include "../ConfigFile/ConfigValue.hpp"
#include "../Project.hpp"

class HttpConfig
{
  private:
	std::istringstream fileContent;

  public:
	/* Cannonical form*/
	HttpConfig(void);
	HttpConfig(ConfigPath fileName);
	HttpConfig(const HttpConfig &other);
	HttpConfig &operator=(const HttpConfig &other);
	~HttpConfig(void);

	/*Getters*/
	const std::istringstream &getFileContent(void) const;

	/*Setters*/
	void setFileContent(std::istringstream &fileContent);

	/*
		Print the configuration
	*/
	void printConfig(void) const;

	/*
		objects holding the information
	*/
	ConfigPath filePath;
	ConfigValue serverCount;
	std::vector<ConfigServer> serverConfigs;
};