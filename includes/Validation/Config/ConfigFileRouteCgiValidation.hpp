#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteCgiValidation : public ConfigFileObjectValidation
{
  private:
	/*Private varibales*/
	bool cgiSymbol;
	bool cgiPermission;
	bool cgiExtension;
	bool cgiPermissionValue;
	std::string cgiExtensionValue;

	/*Helper fucntions*/
	bool validateCgiSymbol(std::string &line);
	bool validateCgi(std::string &line);
	bool validateCgiPermission(std::string &line);
	bool validateCgiExtension(std::string &extension);

  public:
	/* Cannonical form */
	ConfigFileRouteCgiValidation(void);
	ConfigFileRouteCgiValidation(const ConfigFileRouteCgiValidation &other);
	ConfigFileRouteCgiValidation &operator=(const ConfigFileRouteCgiValidation &other);
	~ConfigFileRouteCgiValidation(void);

	/*
		Function to validate the configuration file
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getCgiSymbol(void) const;
	bool getCgiPermission(void) const;
	bool getCgiExtension(void) const;
	bool getCgiPermissionValue(void) const;
	std::string getCgiExtensionValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};