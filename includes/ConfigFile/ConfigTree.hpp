#pragma once

#include "../Project.hpp"

class ConfigTree
{
  private:
	/* Private variables */
	bool autoindex;

  public:
	/* Cannonical form*/
	ConfigTree(void);
	ConfigTree(bool autoindex);
	ConfigTree(const ConfigTree &other);
	ConfigTree &operator=(const ConfigTree &other);
	~ConfigTree(void);

	/* Getters */
	bool getAutoindex(void) const;

	/* Setters */
	void setAutoindex(const bool &autoindex);
};