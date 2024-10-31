#include "../../../includes/Validation/Config/ConfigFileObjectValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileObjectValidation::ConfigFileObjectValidation(void)
{
}

ConfigFileObjectValidation::ConfigFileObjectValidation(const ConfigFileObjectValidation &other)
{
	*this = other;
}

ConfigFileObjectValidation &ConfigFileObjectValidation::operator=(const ConfigFileObjectValidation &other)
{
	(void)other;
	return (*this);
}

ConfigFileObjectValidation::~ConfigFileObjectValidation(void)
{
}

/*PROTECTED FUNCTIONS*/

/*
	Function to split a string by a delimiter this one is assigned by limit
*/
std::vector<std::string> ConfigFileObjectValidation::split(const std::string &str, char limit) const
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, limit))
		tokens.push_back(token);
	return (tokens);
}
