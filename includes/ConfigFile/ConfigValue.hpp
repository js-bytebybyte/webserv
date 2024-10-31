#pragma once

#include "../Project.hpp"

class ConfigValue
{
  private:
	/* Private variables */
	int amount;

  public:
	/* Cannonical form*/
	ConfigValue(void);
	ConfigValue(int value);
	ConfigValue(const ConfigValue &other);
	ConfigValue &operator=(const ConfigValue &other);
	~ConfigValue(void);

	/* Getters */
	int getValue(void) const;

	/* Setters */
	void setValue(const int &value);
};