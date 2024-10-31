#pragma once

#include "../Project.hpp"
#include "../Validation/Config/ConfigFileBlockValidation.hpp"
#include "../Validation/Config/ConfigFileRouteValidation.hpp"
#include "../Validation/Config/ConfigFileServerValidation.hpp"
#include "../Validation/Config/ConfigFinalValidation.hpp"
#include "../Validation/Config/ConfigPreValidation.hpp"

class ConfigValidator
{
  public:
	/* Cannonical form*/
	ConfigValidator(void);
	ConfigValidator(const ConfigValidator &other);
	ConfigValidator &operator=(const ConfigValidator &other);
	~ConfigValidator(void);

	/*
		All the components that are needed to validate the configuration file
	*/
	ConfigPreValidation configPreValidation;
	ConfigFileBlockValidation configFileBlockValidation;
	ConfigFileServerValidation configFileServerValidation;
	ConfigFileRouteValidation configFileRouteValidation;
	ConfigFinalValidation configFinalValidation;
};