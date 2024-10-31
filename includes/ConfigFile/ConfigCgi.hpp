#pragma once

#include "../Project.hpp"

class ConfigCgi
{
  private:
	/* Private variables */
	bool authorized;
	std::string extension;

  public:
	/* Cannonical form*/
	ConfigCgi(void);
	ConfigCgi(bool autoindex);
	ConfigCgi(const ConfigCgi &other);
	ConfigCgi &operator=(const ConfigCgi &other);
	~ConfigCgi(void);

	/* Getters */
	bool getAuthorized(void) const;
	std::string getExtension(void) const;

	/* Setters */
	void setAuthorized(const bool &authorized);
	void setExtension(const std::string &extension);
};