#include "../../../includes/Parsing/Config/ConfigParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigParsing::ConfigParsing(void) : configValidator()
{
}

ConfigParsing::ConfigParsing(const ConfigParsing &other)
{
	*this = other;
}

ConfigParsing &ConfigParsing::operator=(const ConfigParsing &other)
{
	if (this != &other)
		configValidator = other.configValidator;
	return (*this);
}

ConfigParsing::~ConfigParsing(void)
{
}

/*
	Function to print an error message
*/
void ConfigParsing::printError(const std::string &message) const
{
	std::cout << TRED << "Error: " << message << TRESET << std::endl;
}

/*
	Function to split a string by a delimiter this one is assinged by limit
*/
std::vector<std::string> ConfigParsing::split(const std::string &str,
	char limit) const
{
	std::vector<std::string> tokens; // contain all tokens already splitted
	std::string token;               // current token found
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, limit))
		tokens.push_back(token);
	return (tokens);
}

/*
	Function to skip a number of lines
*/
std::string ConfigParsing::skipLines(std::istringstream &stream, const int numLines)
{
	std::string line;
	// Skip the specified number of lines
	for (int i = 0; i < numLines; ++i)
	{
		if (!std::getline(stream, line))
			break ;
	}
	// Collect the remaining content
	std::string remainingContent;
	std::string temp;
	while (std::getline(stream, temp))
	{
		remainingContent += temp;
		if (!stream.eof())
			remainingContent += '\n';
	}
	return (remainingContent);
}
