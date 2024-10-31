#include "../../includes/Parser/ParserElement.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ParserElement::ParserElement(void) : requestParser(), configParser()
{
}

ParserElement::ParserElement(const ParserElement &other)
{
	*this = other;
}

ParserElement &ParserElement::operator=(const ParserElement &other)
{
	if (this != &other)
	{
		requestParser = other.requestParser;
		configParser = other.configParser;
	}
	return (*this);
}

ParserElement::~ParserElement(void)
{
}

/*
	Function to print an error message
*/
void ParserElement::printError(const std::string &message) const
{
	std::cout << TRED << "Error: " << message << TRESET << std::endl;
}