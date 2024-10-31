#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerDomainValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool domainSymbol;
	bool domain;
	std::vector<std::string> domains;

	/*
		Helper functions
	*/
	bool validateDomain(const std::string &domain);
	bool validateSingleDomain(const std::string &domain);
	bool validateDomains(std::string &line);

  public:
	ConfigFileServerDomainValidation(void);
	ConfigFileServerDomainValidation(const ConfigFileServerDomainValidation &other);
	ConfigFileServerDomainValidation &operator=(const ConfigFileServerDomainValidation &other);
	~ConfigFileServerDomainValidation(void);

	/*
		Function to validate the "domains" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getDomainSymbol(void) const;
	bool getDomain(void) const;
	std::vector<std::string> getDomains(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);
};