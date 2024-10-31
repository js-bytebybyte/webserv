#include "../../../includes/Parsing/Config/ConfigFileParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileParsing::ConfigFileParsing(void)
{
}

ConfigFileParsing::ConfigFileParsing(const ConfigFileParsing &other) : ConfigParsing(other)
{
	*this = other;
}

ConfigFileParsing &ConfigFileParsing::operator=(const ConfigFileParsing &other)
{
	(void)other;
	return (*this);
}

ConfigFileParsing::~ConfigFileParsing(void)
{
}

/*PROTECTED FUNCTIONS*/

/*
	function to read the configuration file
*/
std::string ConfigFileParsing::readFile(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return (printError(OPENF + filename), "");
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}