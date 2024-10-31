#include "../../../includes/Validation/Config/ConfigFileRouteUploadValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileRouteUploadValidation::ConfigFileRouteUploadValidation(void) : uploadSymbol(false), upload(false), uploadValue(""), entry("")
{
}

ConfigFileRouteUploadValidation::ConfigFileRouteUploadValidation(const ConfigFileRouteUploadValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileRouteUploadValidation &ConfigFileRouteUploadValidation::operator=(const ConfigFileRouteUploadValidation &other)
{
	if (this != &other)
	{
		uploadSymbol = other.uploadSymbol;
		upload = other.upload;
		uploadValue = other.uploadValue;
		entry = other.entry;
	}
	return (*this);
}

ConfigFileRouteUploadValidation::~ConfigFileRouteUploadValidation(void)
{
}

/*
	Function to validate the configuration file
*/
bool ConfigFileRouteUploadValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateUploadSymbol(line))
		return (false);
	if (!validateUpload(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileRouteUploadValidation::getUploadSymbol(void) const
{
	return (uploadSymbol);
}

bool ConfigFileRouteUploadValidation::getUpload(void) const
{
	return (upload);
}

std::string ConfigFileRouteUploadValidation::getUploadValue(void) const
{
	return (uploadValue);
}

/*Helper functions*/
void ConfigFileRouteUploadValidation::reset(void)
{
	uploadSymbol = false;
	upload = false;
	uploadValue = "";
	entry = "";
}

/*Setters*/
void ConfigFileRouteUploadValidation::setEntry(std::string entry)
{
	this->entry = entry;
}

/*PRIVATE FUNCTIONS*/
bool ConfigFileRouteUploadValidation::validateUploadSymbol(std::string &line)
{
	if (strncmp(line.c_str(), UPLOADKEY, strlen(UPLOADKEY)) != 0)
		return (false);
	uploadSymbol = true;
	return (true);
}

bool ConfigFileRouteUploadValidation::validateUpload(std::string &line)
{
	if (line.empty())
		return (false);
	line = line.substr(strlen(UPLOADKEY));
	std::vector<std::string> args = split(line, ' ');
	if (args.size() != 2)
		return (false);
	if (args[1] != DELIMITTER)
		return (false);
	args.pop_back();
	if (args[0].empty())
		return (false);
	std::string upload = entry + args[0];
	if (!validatePath(upload))
		return (false);
	return (true);
}

bool ConfigFileRouteUploadValidation::validatePath(std::string &path)
{
	int	fd;

	fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	upload = true;
	uploadValue = path;
	return (true);
}
