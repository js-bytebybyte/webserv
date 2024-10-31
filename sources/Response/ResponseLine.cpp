#include "../../includes/Response/ResponseLine.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
ResponseLine::ResponseLine(void) : fullStatus(""), http(""), statusCode(UNDEFINED), reason("")
{
}

ResponseLine::ResponseLine(const ResponseLine &other)
{
	*this = other;
}

ResponseLine &ResponseLine::operator=(const ResponseLine &other)
{
	if (this != &other)
	{
		fullStatus = other.fullStatus;
		http = other.http;
		statusCode = other.statusCode;
		reason = other.reason;
	}
	return (*this);
}

ResponseLine::~ResponseLine(void)
{
}

/*Getters*/
std::string ResponseLine::getFullStatus(void) const
{
	return (fullStatus);
}

std::string ResponseLine::getHttp(void) const
{
	return (http);
}

unsigned int ResponseLine::getStatusCode(void) const
{
	return (statusCode);
}

std::string ResponseLine::getReason(void) const
{
	return (reason);
}

/*Setters*/
void ResponseLine::setFullStatus(const std::string &full)
{
	fullStatus = full;
}

void ResponseLine::setHttp(const std::string &http)
{
	this->http = http;
}

void ResponseLine::setStatusCode(const unsigned int &status)
{
	statusCode = status;
}

void ResponseLine::setReason(const std::string &reason)
{
	this->reason = reason;
}
