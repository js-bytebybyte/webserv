#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteRedirectValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool redirectSymbol;
	bool redirect;
	std::string redirectValue;

	/*
		Helper functions
	*/
	bool validateRedirectPrefix(std::string &line);
	bool validateRedirect(std::string &line);

  public:
	/* Cannonical form */
	ConfigFileRouteRedirectValidation(void);
	ConfigFileRouteRedirectValidation(const ConfigFileRouteRedirectValidation &other);
	ConfigFileRouteRedirectValidation &operator=(const ConfigFileRouteRedirectValidation &other);
	~ConfigFileRouteRedirectValidation(void);

	/*
		Function to validate the "redirect" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getRedirectSymbol(void) const;
	bool getRedirect(void) const;
	std::string getRedirectValue(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};