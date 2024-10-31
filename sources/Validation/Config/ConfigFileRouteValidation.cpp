#include "../../../includes/Validation/Config/ConfigFileRouteValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

ConfigFileRouteValidation::ConfigFileRouteValidation(void) : seenLines(0), seenRoutes(0), validRoute(false), route(),
	method(), redirect(), entry(), tree(),
	index(), upload(), cgi()
{
}

ConfigFileRouteValidation::ConfigFileRouteValidation(const ConfigFileRouteValidation &other)
{
	*this = other;
}

ConfigFileRouteValidation &ConfigFileRouteValidation::operator=(const ConfigFileRouteValidation &other)
{
	if (this != &other)
	{
		seenLines = other.seenLines;
		seenRoutes = other.seenRoutes;
		validRoute = other.validRoute;
		route = other.route;
		method = other.method;
		redirect = other.redirect;
		entry = other.entry;
		tree = other.tree;
		index = other.index;
		upload = other.upload;
		cgi = other.cgi;
	}
	return (*this);
}

ConfigFileRouteValidation::~ConfigFileRouteValidation(void)
{
}

/*
	Function to validate the configuration file
*/
void ConfigFileRouteValidation::validateRouteBlock(HttpConfig &config)
{
	ConfigFileObjectValidation	*validators[] = {&method, &redirect, &entry, &tree};
	ConfigFileObjectValidation	*validate[] = {&index, &upload, &cgi};

	std::istringstream file(config.getFileContent().str());
	std::string line;
	std::cout << TMAGENTA << line << TRESET << std::endl;
	if (!route.validate(file, line))
		return ;
	seenLines++;
	seenRoutes++;
	// loop through the validators to validate the config file
	for (int i = 0; i < 4; i++)
	{
		std::cout << TMAGENTA << line << TRESET << std::endl;
		if (!validators[i]->validate(file, line))
			return ;
		seenLines++;
	}
	index.setEntry(entry.getEntryPoint());
	upload.setEntry(entry.getEntryPoint());
	for (int i = 0; i < 3; i++)
	{
		std::cout << TMAGENTA << line << TRESET << std::endl;
		if (!validate[i]->validate(file, line))
			return ;
		seenLines++;
	}
	std::getline(file, line);
	std::cout << TMAGENTA << line << TRESET << std::endl;
	if (!(strcmp(line.c_str(), ENDROUTE) == 0))
		return ;
	validRoute = true;
	seenLines++;
}

/*Getters*/
int ConfigFileRouteValidation::getSeenLines(void) const
{
	return (seenLines);
}

int ConfigFileRouteValidation::getSeenRoutes(void) const
{
	return (seenRoutes);
}

bool ConfigFileRouteValidation::getValidRoute(void) const
{
	return (validRoute);
}

/*Helper functions*/
void ConfigFileRouteValidation::reset(void)
{
	seenLines = 0;
	validRoute = false;
	route.reset();
	method.reset();
	redirect.reset();
	entry.reset();
	tree.reset();
	index.reset();
	upload.reset();
	cgi.reset();
}

/*Setters*/
void ConfigFileRouteValidation::setSeenLines(const int &seenLines)
{
	this->seenLines = seenLines;
}

void ConfigFileRouteValidation::setSeenRoutes(const int &seenRoutes)
{
	this->seenRoutes = seenRoutes;
}