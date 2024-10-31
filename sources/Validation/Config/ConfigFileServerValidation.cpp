#include "../../../includes/Validation/Config/ConfigFileServerValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerValidation::ConfigFileServerValidation(void) : seenRoutes(0), seenLines(0), validServer(false), matchingRoutes(false),
	serverErrors(), listen(), domain(), entry(),
	bodySize(), route(), header(), error()
{
}

ConfigFileServerValidation::ConfigFileServerValidation(const ConfigFileServerValidation &other)
{
	*this = other;
}

ConfigFileServerValidation &ConfigFileServerValidation::operator=(const ConfigFileServerValidation &other)
{
	if (this != &other)
	{
		seenRoutes = other.seenRoutes;
		seenLines = other.seenLines;
		validServer = other.validServer;
		matchingRoutes = other.matchingRoutes;
		serverErrors = other.serverErrors;
		listen = other.listen;
		domain = other.domain;
		entry = other.entry;
		bodySize = other.bodySize;
		route = other.route;
		header = other.header;
		error = other.error;
	}
	return (*this);
}

ConfigFileServerValidation::~ConfigFileServerValidation(void)
{
}

/*
	Function to validate the configuration file
*/
void ConfigFileServerValidation::validateBeginBlock(HttpConfig &config)
{
	ConfigFileObjectValidation	*validators[] = {&header, &listen, &domain, &entry};
	ConfigFileObjectValidation	*valid[] = {&bodySize, &route};

	std::istringstream file(config.getFileContent().str());
	std::string line;
	// loop through the validatorsn to validate the config file
	for (int i = 0; i < 4; i++)
	{
		std::cout << TYELLOW << line << TRESET << std::endl;
		if (!validators[i]->validate(file, line))
			return ;
		seenLines++;
	}
	error.setEntry(entry.getEntryPoint());
	std::cout << TYELLOW << line << TRESET << std::endl;
	if (!error.validate(file, line))
		return ;
	seenLines++;
	serverErrors.resize(error.getExpectedErrors(), std::make_pair(error.getErrorPath(), error.getCodesErrors()));
	// since you defined the expected errors, you can loop through the errors
	for (int i = 0; i < error.getExpectedErrors(); i++)
	{
		std::cout << TYELLOW << line << TRESET << std::endl;
		if (!error.validate(file, line))
			return ;
		serverErrors[i] = std::make_pair(error.getErrorPath(), error.getCodesErrors());
		seenLines++;
		// reset all the flags for each loop
		error.resetFlags();
	}
	// loop through the valid array to validate the config file the last part
	for (int i = 0; i < 2; i++)
	{
		std::cout << TYELLOW << line << TRESET << std::endl;
		if (!valid[i]->validate(file, line))
			return ;
		seenLines++;
	}
}

// NEED TO DO THE VALIDATION FOR THE END BLOCK
void ConfigFileServerValidation::validateEndBlock(HttpConfig &config)
{
	seenLines = 0;
	std::istringstream file(config.getFileContent().str());
	std::string line;
	std::getline(file, line);
	std::cout << TYELLOW << line << TRESET << std::endl;
	seenLines++;
	if (!(route.getExpectedRoutes() == seenRoutes))
		return ;
	matchingRoutes = true;
	if (!(strcmp(line.c_str(), ENDSERVER) == 0))
		return ;
	validServer = true;
}

/*Getters*/
int ConfigFileServerValidation::getSeenLines(void) const
{
	return (seenLines);
}

bool ConfigFileServerValidation::getValidServer(void) const
{
	return (validServer);
}

bool ConfigFileServerValidation::getMatchingRoutes(void) const
{
	return (matchingRoutes);
}

int ConfigFileServerValidation::getSeenRoutes(void) const
{
	return (seenRoutes);
}

std::vector<std::pair<std::string, std::vector<std::string> > > ConfigFileServerValidation::getServerErrors(void) const
{
	return (serverErrors);
}

/*
	Function to reset the object
*/
void ConfigFileServerValidation::reset(void)
{
	seenLines = 0;
	seenRoutes = 0;
	validServer = false;
	matchingRoutes = false;
	serverErrors.clear();
	listen.reset();
	domain.reset();
	entry.reset();
	bodySize.reset();
	route.reset();
	header.reset();
	error.reset();
}

/*Setters*/
void ConfigFileServerValidation::setSeenRoutes(const int &seen)
{
	seenRoutes = seen;
}
