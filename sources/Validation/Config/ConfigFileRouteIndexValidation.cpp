#include "../../../includes/Validation/Config/ConfigFileRouteIndexValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileRouteIndexValidation::ConfigFileRouteIndexValidation(void) : indexSymbol(false), index(false), indexValue(""), entry("")
{
}

ConfigFileRouteIndexValidation::ConfigFileRouteIndexValidation(const ConfigFileRouteIndexValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteIndexValidation &ConfigFileRouteIndexValidation::operator=(const ConfigFileRouteIndexValidation &other)
{
	if (this != &other)
	{
		indexSymbol = other.indexSymbol;
		index = other.index;
		indexValue = other.indexValue;
		entry = other.entry;
	}
	return (*this);
}

ConfigFileRouteIndexValidation::~ConfigFileRouteIndexValidation(void)
{
}

/*
	Function to validate the configuration file
*/
bool ConfigFileRouteIndexValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateIndexSymbol(line))
		return (false);
	if (!validateIndex(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteIndexValidation::getIndexSymbol(void) const
{
	return (indexSymbol);
}

bool ConfigFileRouteIndexValidation::getIndex(void) const
{
	return (index);
}

std::string ConfigFileRouteIndexValidation::getIndexValue(void) const
{
	return (indexValue);
}

/*Helper functions*/
void ConfigFileRouteIndexValidation::reset(void)
{
	indexSymbol = false;
	index = false;
	indexValue = "";
	entry = "";
}

/*Setters*/
void ConfigFileRouteIndexValidation::setEntry(std::string entry)
{
	this->entry = entry;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileRouteIndexValidation::validateIndexSymbol(std::string &line)
{
	if (strncmp(line.c_str(), DEFAULTPAGEKEY, strlen(DEFAULTPAGEKEY)) != 0)
		return (false);
	indexSymbol = true;
	return (true);
}

bool ConfigFileRouteIndexValidation::validateIndex(std::string &line)
{
	if (line.empty())
		return (false);
	line = line.substr(strlen(DEFAULTPAGEKEY));
	std::vector<std::string> args = split(line, ' ');
	if (args.size() != 2)
		return (false);
	if (args[1] != DELIMITTER)
		return (false);
	args.pop_back();
	if (args[0].empty())
		return (false);
	std::string index = entry + args[0];
	if (!validatePath(index))
		return (false);
	return (true);
}

bool ConfigFileRouteIndexValidation::validatePath(std::string &path)
{
	int fd;
	fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	indexValue = path;
	index = true;
	return (true);
}