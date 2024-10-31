#include "../../includes/Response/ResponseInformation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
ResponseInformation::ResponseInformation(void) : fullResponse(""), emptyLine(false), validResponse(false), completeResponse(false)
{
}

ResponseInformation::ResponseInformation(const std::string &raw) : fullResponse(raw), emptyLine(false), validResponse(false), completeResponse(false)
{
}

ResponseInformation::ResponseInformation(const ResponseInformation &other)
{
	*this = other;
}

ResponseInformation &ResponseInformation::operator=(const ResponseInformation &other)
{
	if (this != &other)
	{
		fullResponse = other.fullResponse;
		emptyLine = other.emptyLine;
		validResponse = other.validResponse;
		completeResponse = other.completeResponse;
	}
	return (*this);
}

ResponseInformation::~ResponseInformation(void)
{
}

/*Getters*/
std::string ResponseInformation::getFullResponse(void) const
{
	return (fullResponse);
}

bool ResponseInformation::getEmptyLine(void) const
{
	return (emptyLine);
}

bool ResponseInformation::getValidResponse(void) const
{
	return (validResponse);
}

bool ResponseInformation::getCompleteResponse(void) const
{
	return (completeResponse);
}

/*Setters*/
void ResponseInformation::setFullResponse(const std::string &raw)
{
	fullResponse = raw;
}

void ResponseInformation::setEmptyLine(const bool &b)
{
	emptyLine = b;
}

void ResponseInformation::setValidResponse(const bool &b)
{
	validResponse = b;
}

void ResponseInformation::setCompleteResponse(const bool &b)
{
	completeResponse = b;
}
