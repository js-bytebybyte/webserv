#include "../../includes/Request/RequestInformation.hpp"

/*PUBLIC FUNCTIONS*/

// Canonical form
RequestInformation::RequestInformation(void) : full("NULL"), status(OK), emptyLine(false), validRequest(true),
	completeRequest(false), chunked(false), rBuff(NULL)
{
}

RequestInformation::RequestInformation(const std::string &raw) : full(raw), status(OK), emptyLine(false), validRequest(true),
	completeRequest(false), chunked(false), rBuff(NULL)
{
}

RequestInformation::RequestInformation(const RequestInformation &other)
{
	*this = other;
}

RequestInformation &RequestInformation::operator=(const RequestInformation &other)
{
	if (this != &other)
	{
		full = other.full;
		status = other.status;
		emptyLine = other.emptyLine;
		validRequest = other.validRequest;
		completeRequest = other.completeRequest;
		chunked = other.chunked;
		rBuff = other.rBuff;
	}
	return (*this);
}

RequestInformation::~RequestInformation(void)
{
}

/*Getters*/
std::string RequestInformation::getFullRequest(void) const
{
	return (full);
}

unsigned int RequestInformation::getStatus(void) const
{
	return (status);
}

bool RequestInformation::getEmptyLine(void) const
{
	return (emptyLine);
}

bool RequestInformation::getValidRequest(void) const
{
	return (validRequest);
}

bool RequestInformation::getCompleteRequest(void) const
{
	return (completeRequest);
}

bool RequestInformation::getChunked(void) const
{
	return (chunked);
}

char *RequestInformation::getrBuff(void) const
{
	return (rBuff);
}

/*Setters*/
void RequestInformation::setFullRequest(const std::string &raw)
{
	full = raw;
}

void RequestInformation::setStatus(const unsigned int &s)
{
	status = s;
}

void RequestInformation::setEmptyLine(const bool &b)
{
	emptyLine = b;
}

void RequestInformation::setValidRequest(const bool &b)
{
	validRequest = b;
}

void RequestInformation::setCompleteRequest(const bool &b)
{
	completeRequest = b;
}

void RequestInformation::setChunked(const bool &b)
{
	chunked = b;
}

void RequestInformation::setrBuff(const char *buff)
{
	rBuff = const_cast<char *>(buff);
}