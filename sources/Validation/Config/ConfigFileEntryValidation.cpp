#include "../../../includes/Validation/Config/ConfigFileEntryValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileEntryValidation::ConfigFileEntryValidation(void) : entrySymbol(false), entry(false), entryPoint("")
{
}

ConfigFileEntryValidation::ConfigFileEntryValidation(const ConfigFileEntryValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileEntryValidation &ConfigFileEntryValidation::operator=(const ConfigFileEntryValidation &other)
{
	if (this != &other)
	{
		entrySymbol = other.entrySymbol;
		entry = other.entry;
		entryPoint = other.entryPoint;
	}
	return (*this);
}

ConfigFileEntryValidation::~ConfigFileEntryValidation(void)
{
}

/*
	Function to validate the "entry" directive
*/
bool ConfigFileEntryValidation::validate(std::istringstream &file, std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateEntry(line))
		return (false);
	if (!validateEntryValue(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileEntryValidation::getEntrySymbol(void) const
{
	return (entrySymbol);
}

bool ConfigFileEntryValidation::getEntry(void) const
{
	return (entry);
}

std::string ConfigFileEntryValidation::getEntryPoint(void) const
{
	return (entryPoint);
}

/*Helper functions*/
void ConfigFileEntryValidation::reset(void)
{
	entrySymbol = false;
	entry = false;
	entryPoint = "";
}

/*Setters*/
void ConfigFileEntryValidation::setEntryPoint(const std::string &entry)
{
	entryPoint = entry;
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions to validate the "domains" directive
*/
bool ConfigFileEntryValidation::validateEntry(const std::string &entry)
{
	int	size;

	size = std::strlen(ENTRYKEY);
	if (std::strncmp(entry.c_str(), ENTRYKEY, size) != 0)
		return (false);
	entrySymbol = true;
	return (true);
}

bool ConfigFileEntryValidation::validateEntryValue(std::string &line)
{
	int	fd;

	line = line.substr(strlen(ENTRYKEY));
	std::vector<std::string> entryArgs = split(line, ' ');
	if (entryArgs.size() != 2)
		return (false);
	if (entryArgs[1] != DELIMITTER)
		return (false);
	if (entryArgs[0].empty())
		return (false);
	// Check if it is a directory
	std::string path = entryArgs[0];
	fd = open(path.c_str(), DIRREAD);
	if (fd < 0)
		return (false);
	close(fd);
	entry = true;
	entryPoint = path;
	return (true);
}
