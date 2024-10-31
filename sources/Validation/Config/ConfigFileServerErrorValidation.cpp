#include "../../../includes/Validation/Config/ConfigFileServerErrorValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerErrorValidation::ConfigFileServerErrorValidation(void) : entry(""), seenErrors(0), expectedErrors(0), errorsAmountSymbol(false),
	errorsAmount(false), errorsSymbol(false), errors(false), codesErrors(),
	errorPath("")
{
}

ConfigFileServerErrorValidation::ConfigFileServerErrorValidation(const ConfigFileServerErrorValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerErrorValidation &ConfigFileServerErrorValidation::operator=(const ConfigFileServerErrorValidation &other)
{
	if (this != &other)
	{
		entry = other.entry;
		seenErrors = other.seenErrors;
		expectedErrors = other.expectedErrors;
		errorsAmountSymbol = other.errorsAmountSymbol;
		errorsAmount = other.errorsAmount;
		errorsSymbol = other.errorsSymbol;
		errors = other.errors;
		codesErrors = other.codesErrors;
		errorPath = other.errorPath;
	}
	return (*this);
}

ConfigFileServerErrorValidation::~ConfigFileServerErrorValidation(void)
{
}

/*
	Function to validate the "errors" directive
*/
bool ConfigFileServerErrorValidation::validate(std::istringstream &file, std::string &line)
{
	if (!std::getline(file, line))
		return (false);
	if (strncmp(line.c_str(), VALUEKEY, strlen(VALUEKEY)) == 0)
	{
		if (!validateErrorsAmountDirective(line))
			return (false);
	}
	else
	{
		seenErrors++;
		if (!validateErrorsDirective(line))
			return (false);
	}
	return (true);
}

/*Getters*/
int ConfigFileServerErrorValidation::getSeenErrors(void) const
{
	return (seenErrors);
}

int ConfigFileServerErrorValidation::getExpectedErrors(void) const
{
	return (expectedErrors);
}

bool ConfigFileServerErrorValidation::getErrorsAmountSymbol(void) const
{
	return (errorsAmountSymbol);
}

bool ConfigFileServerErrorValidation::getErrorsAmount(void) const
{
	return (errorsAmount);
}

bool ConfigFileServerErrorValidation::getErrorsSymbol(void) const
{
	return (errorsSymbol);
}

bool ConfigFileServerErrorValidation::getErrors(void) const
{
	return (errors);
}

std::vector<std::string> ConfigFileServerErrorValidation::getCodesErrors(void) const
{
	return (codesErrors);
}

std::string ConfigFileServerErrorValidation::getErrorPath(void) const
{
	return (errorPath);
}

/*
	Function to reset the flags
*/
void ConfigFileServerErrorValidation::reset(void)
{
	seenErrors = 0;
	expectedErrors = 0;
	errorsAmountSymbol = false;
	errorsAmount = false;
	errorsSymbol = false;
	errors = false;
	codesErrors.clear();
	errorPath = "";
}

void ConfigFileServerErrorValidation::resetFlags(void)
{
	if (seenErrors < expectedErrors)
	{
		errorsSymbol = false;
		errors = false;
	}
}

/*Setters*/
void ConfigFileServerErrorValidation::setEntry(const std::string &entry)
{
	this->entry = entry;
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
bool ConfigFileServerErrorValidation::validateErrorsAmountDirective(std::string &line)
{
	if (std::strncmp(line.c_str(), VALUEKEY, strlen(VALUEKEY)) != 0)
		return (false);
	errorsAmountSymbol = true;
	if (std::sscanf(line.c_str(), VALUEPATTERN, &expectedErrors) != 1)
		return (false);
	if (expectedErrors <= 0 || INT16_MAX <= expectedErrors)
		return (false);
	errorsAmount = true;
	return (true);
}

bool ConfigFileServerErrorValidation::validateErrorsDirective(std::string &line)
{
	if (!validateErrorsPrefix(line))
		return (false);
	line = line.substr(strlen(ERRORKEY));
	std::vector<std::string> errorArgs = split(line, ' ');
	if (!validateErrorsArgs(errorArgs))
		return (false);
	return (true);
}

bool ConfigFileServerErrorValidation::validateErrorsPrefix(std::string &line)
{
	if (std::strncmp(line.c_str(), ERRORKEY, strlen(ERRORKEY)) != 0)
		return (false);
	errorsSymbol = true;
	return (true);
}

bool ConfigFileServerErrorValidation::validateErrorsArgs(std::vector<std::string> &errorArgs)
{
	if (errorArgs.empty())
		return (false);
	if (errorArgs.back() != DELIMITTER)
		return (false);
	errorArgs.pop_back(); // Remove ";" for further validation
	if (errorArgs.size() == 1)
	{
		// allow no errors
		if (errorArgs[0] != NOBODY)
			return (false);
	}
	else
	{
		std::string combinedPath = entry + errorArgs[0];
		if (!validatePath(combinedPath))
			return (false);
		std::string errorCodes = errorArgs[1];
		if (!validateErrorsCodes(errorCodes))
			return (false);
	}
	errors = true;
	return (true);
}

bool ConfigFileServerErrorValidation::validatePath(std::string &path)
{
	int	fd;

	fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	errorPath = path;
	return (true);
}

bool ConfigFileServerErrorValidation::validateErrorsCodes(const std::string &codes)
{
	int size = codes.size();
	if (codes.empty() || codes[0] != BEGINARRAY || codes[size - 1] != ENDARRAY)
		return (false);

	std::string onlyCodes = codes.substr(1, codes.size() - 2);
	std::vector<std::string> codeList;
	std::stringstream ss(onlyCodes);
	std::string code;
	std::string separator = SEPARTOR;
	char symbol = separator[0];
	while (std::getline(ss, code, symbol))
	{
		int ok = (!isdigit(code[0]) || !isdigit(code[1]) || !isdigit(code[2]));
		if (code.size() != 3 || ok)
			return (false);
		codeList.push_back(code);
	}
	codesErrors = codeList;
	return (true);
}