#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileServerErrorValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	std::string entry;
	int seenErrors;
	int expectedErrors;
	bool errorsAmountSymbol;
	bool errorsAmount;
	bool errorsSymbol;
	bool errors;
	std::vector<std::string> codesErrors;
	std::string errorPath;

	/*
		Helper functions
	*/
	bool validateErrorsAmountDirective(std::string &line);
	bool validateErrorsDirective(std::string &line);
	bool validateErrorsPrefix(std::string &line);
	bool validateErrorsArgs(std::vector<std::string> &args);
	bool validatePath(std::string &path);
	bool validateErrorsCodes(const std::string &errorCodes);

  public:
	/* Cannonical form */
	ConfigFileServerErrorValidation(void);
	ConfigFileServerErrorValidation(const ConfigFileServerErrorValidation &other);
	ConfigFileServerErrorValidation &operator=(const ConfigFileServerErrorValidation &other);
	virtual ~ConfigFileServerErrorValidation(void);

	/*
		Function to validate the configuration file
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	int getSeenErrors(void) const;
	int getExpectedErrors(void) const;
	bool getErrorsAmountSymbol(void) const;
	bool getErrorsAmount(void) const;
	bool getErrorsSymbol(void) const;
	bool getErrors(void) const;
	std::vector<std::string> getCodesErrors(void) const;
	std::string getErrorPath(void) const;

	/*
		Function to reset the flags
	*/
	void reset(void);
	void resetFlags(void);

	/*Setters*/
	void setEntry(const std::string &entry);
};
