#include "../../../includes/Parsing/Request/RequestParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
RequestParsing::RequestParsing(void) : requestValidator()
{
}

RequestParsing::~RequestParsing(void)
{
}

RequestParsing::RequestParsing(const RequestParsing &other)
{
	*this = other;
}

RequestParsing &RequestParsing::operator=(const RequestParsing &other)
{
	if (this != &other)
		requestValidator = other.requestValidator;
	return (*this);
}

/*PROTECTED FUNCTIONS*/

/*
	Helper function to trim whitespace from both ends of a string
*/
std::string RequestParsing::trim(const std::string &str) const
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");
	std::string trimmed;

	if (start == std::string::npos)
		trimmed = "";
	else
		trimmed = str.substr(start, end - start + 1);
	return (trimmed);
}

/*
	Function to split a string by a delimiter this one is assinged by limit
*/
std::vector<std::string> RequestParsing::split(const std::string &str, char limit) const
{
	std::vector<std::string> tokens; // contain all tokens already splitted
	std::string token;               // current token found
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, limit))
		tokens.push_back(token);
	return (tokens);
}