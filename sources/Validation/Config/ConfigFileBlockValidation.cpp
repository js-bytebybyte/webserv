#include "../../../includes/Validation/Config/ConfigFileBlockValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileBlockValidation::ConfigFileBlockValidation(void) : seenServers(0), expectedServers(0), seenLines(0), validConfigHeader(false),
	serverAmountSymbol(false), serverAmout(false), validConfig(false), matchingServers(false)
{
}

ConfigFileBlockValidation::ConfigFileBlockValidation(const ConfigFileBlockValidation &other)
{
	*this = other;
}

ConfigFileBlockValidation &ConfigFileBlockValidation::operator=(const ConfigFileBlockValidation &other)
{
	if (this != &other)
	{
		seenServers = other.seenServers;
		expectedServers = other.expectedServers;
		seenLines = other.seenLines;
		validConfigHeader = other.validConfigHeader;
		serverAmountSymbol = other.serverAmountSymbol;
		serverAmout = other.serverAmout;
		validConfig = other.validConfig;
		matchingServers = other.matchingServers;
	}
	return (*this);
}

ConfigFileBlockValidation::~ConfigFileBlockValidation(void)
{
}

/*
	Function to validate the configuration file
*/
void ConfigFileBlockValidation::validateBeginBlock(const HttpConfig &config)
{
	std::istringstream file(config.getFileContent().str());
	std::string line;
	std::getline(file, line);
	std::cout << TBLUE << line << TRESET << std::endl;
	if (!validateConfigHeader(line))
		return ;
	std::getline(file, line);
	std::cout << TBLUE << line << TRESET << std::endl;
	if (!validateServerAmountSymbol(line))
		return ;
	if (!validateServerAmount(line))
		return ;
}

void ConfigFileBlockValidation::validateEndBlock(const HttpConfig &config)
{
	std::istringstream file(config.getFileContent().str());
	std::string line;
	std::cout << TBLUE << line << TRESET << std::endl;
	if (!validateMatchingServers())
		return ;
	if (!validateConfig(file, line))
		return ;
	return ;
}

/*Getters*/
int ConfigFileBlockValidation::getSeenServers(void) const
{
	return (seenServers);
}

int ConfigFileBlockValidation::getExpectedServers(void) const
{
	return (expectedServers);
}

int ConfigFileBlockValidation::getSeenLines(void) const
{
	return (seenLines);
}

bool ConfigFileBlockValidation::getValidConfig(void) const
{
	return (validConfig);
}

bool ConfigFileBlockValidation::getServerAmout(void) const
{
	return (serverAmout);
}

bool ConfigFileBlockValidation::getServerAmountSymbol(void) const
{
	return (serverAmountSymbol);
}

bool ConfigFileBlockValidation::getValidConfigHeader(void) const
{
	return (validConfigHeader);
}

bool ConfigFileBlockValidation::getMatchingServers(void) const
{
	return (matchingServers);
}

/*Setters*/
void ConfigFileBlockValidation::setSeenServers(const int &seen)
{
	seenServers = seen;
}

void ConfigFileBlockValidation::setSeenLines(const int &seen)
{
	seenLines = seen;
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool ConfigFileBlockValidation::validateConfigHeader(const std::string &line)
{
	if (!(strcmp(line.c_str(), BEGINCONF) == 0))
		return (false);
	validConfigHeader = true;
	seenLines++;
	return (true);
}

bool ConfigFileBlockValidation::validateServerAmountSymbol(const std::string &line)
{
	if (!(strncmp(line.c_str(), VALUEKEY, 2) == 0))
		return (false);
	serverAmountSymbol = true;
	seenLines++;
	return (true);
}

bool ConfigFileBlockValidation::validateServerAmount(const std::string &line)
{
	if (!(sscanf(line.c_str(), VALUEPATTERN, &expectedServers) == 1))
		return (false);
	if (expectedServers <= 0 || INT16_MAX <= expectedServers)
		return (false);
	serverAmout = true;
	return (true);
}

bool ConfigFileBlockValidation::validateMatchingServers(void)
{
	if (!(seenServers == expectedServers))
		return (false);
	matchingServers = true;
	return (true);
}

bool ConfigFileBlockValidation::validateConfig(std::istringstream &file, std::string &line)
{
	getline(file, line);
	seenLines++;
	if (!(strcmp(line.c_str(), ENDCONF) == 0))
		return (false);
	if (file.eof())
		validConfig = true;
	getline(file, line);
	seenLines++;
	return (true);
}