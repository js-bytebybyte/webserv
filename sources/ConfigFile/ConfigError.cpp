#include "../../includes/ConfigFile/ConfigError.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigError::ConfigError(void) : errorMessagePath(), errorCodesVector()
{
}

ConfigError::ConfigError(ConfigPath errorMessage, std::vector<int> errorCodes) : errorMessagePath(errorMessage), errorCodesVector(errorCodes)
{
}

ConfigError::ConfigError(const ConfigError &other)
{
	*this = other;
}

ConfigError &ConfigError::operator=(const ConfigError &other)
{
	if (this != &other)
	{
		errorMessagePath = other.errorMessagePath;
		errorCodesVector = other.errorCodesVector;
	}
	return (*this);
}

ConfigError::~ConfigError(void)
{
}
