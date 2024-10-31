#pragma once

#include "../Project.hpp"

class ConfigPath
{
  private:
	/* Private variables */
	std::string string;

  public:
	/* Cannonical form*/
	ConfigPath(void);
	ConfigPath(std::string path);
	ConfigPath(const ConfigPath &other);
	ConfigPath &operator=(const ConfigPath &other);
	~ConfigPath(void);

	/* Getters */
	std::string getPath(void) const;

	/* Setters */
	void setPath(const std::string &path);
};