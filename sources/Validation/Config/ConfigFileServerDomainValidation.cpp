#include "../../../includes/Validation/Config/ConfigFileServerDomainValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerDomainValidation::ConfigFileServerDomainValidation(void) : domainSymbol(false), domain(false), domains()
{
}

ConfigFileServerDomainValidation::ConfigFileServerDomainValidation(const ConfigFileServerDomainValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerDomainValidation &ConfigFileServerDomainValidation::operator=(const ConfigFileServerDomainValidation &other)
{
	if (this != &other)
	{
		domainSymbol = other.domainSymbol;
		domain = other.domain;
		domains = other.domains;
	}
	return (*this);
}

ConfigFileServerDomainValidation::~ConfigFileServerDomainValidation(void)
{
}

/*
	Function to validate the "domains" directive
*/
bool ConfigFileServerDomainValidation::validate(std::istringstream &file,
	std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (!validateDomain(line))
		return (false);
	if (!validateDomains(line))
		return (false);
	return (true);
}

/*Getters*/
bool ConfigFileServerDomainValidation::getDomainSymbol(void) const
{
	return (domainSymbol);
}

bool ConfigFileServerDomainValidation::getDomain(void) const
{
	return (domain);
}

std::vector<std::string> ConfigFileServerDomainValidation::getDomains(void) const
{
	return (domains);
}

/*
	Function to reset the object
*/
void ConfigFileServerDomainValidation::reset(void)
{
	domainSymbol = false;
	domain = false;
	domains.clear();
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigFileServerDomainValidation::validateDomain(const std::string &domain)
{
	int	size;

	size = std::strlen(DOMAINNAME);
	if (std::strncmp(domain.c_str(), DOMAINNAME, size) != 0)
		return (false);
	domainSymbol = true;
	return (true);
}

bool ConfigFileServerDomainValidation::validateSingleDomain(const std::string &domain)
{
	if (domain.size() < strlen(POSTFIX) + 1)
		return (false);
	if (domain.substr(domain.size() - strlen(POSTFIX)) != POSTFIX)
		return (false);
	return (true);
}

bool ConfigFileServerDomainValidation::validateDomains(std::string &line)
{
	line = line.substr(strlen(DOMAINNAME));
	std::vector<std::string> domainsArgs = split(line, ' ');
	if (domainsArgs.empty())
		return (false);
	// Check if the last element is ";"
	if (domainsArgs.back() != DELIMITTER)
		return (false);
	domainsArgs.pop_back(); // Remove ";" for further validation
	if (domainsArgs.size() == 1)
	{
		if (domainsArgs[0] != NOBODY
			&& validateSingleDomain(domainsArgs[0]) == false)
			return (false);
	}
	else
	{
		// Validate each domain
		for (size_t i = 0; i < domainsArgs.size(); i++)
		{
			if (validateSingleDomain(domainsArgs[i]) == false)
				return (false);
		}
	}
	domain = true;
	domains = domainsArgs;
	return (true);
}