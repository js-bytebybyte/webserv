#include "../../includes/Validator/ConfigValidator.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigValidator::ConfigValidator(void) : configPreValidation(), configFileBlockValidation(), configFileServerValidation(), configFileRouteValidation(),
	configFinalValidation()
{
}

ConfigValidator::ConfigValidator(const ConfigValidator &other)
{
	*this = other;
}

ConfigValidator &ConfigValidator::operator=(const ConfigValidator &other)
{
	if (this != &other)
	{
		configPreValidation = other.configPreValidation;
		configFileBlockValidation = other.configFileBlockValidation;
		configFileServerValidation = other.configFileServerValidation;
		configFileRouteValidation = other.configFileRouteValidation;
		configFinalValidation = other.configFinalValidation;
	}
	return (*this);
}

ConfigValidator::~ConfigValidator(void)
{
}
