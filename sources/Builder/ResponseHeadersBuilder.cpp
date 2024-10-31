#include "../../includes/Builder/ResponseHeadersBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseHeadersBuilder::ResponseHeadersBuilder(void) : headers(), date(0), currentTime("")
{
}

ResponseHeadersBuilder::ResponseHeadersBuilder(const ResponseHeadersBuilder &other)
{
	*this = other;
}

ResponseHeadersBuilder &ResponseHeadersBuilder::operator=(const ResponseHeadersBuilder &other)
{
	if (this != &other)
	{
		headers = other.headers;
		date = other.date;
		currentTime = other.currentTime;
	}
	return (*this);
}

ResponseHeadersBuilder::~ResponseHeadersBuilder(void)
{
}

/*
	Function to handle the response
*/
void ResponseHeadersBuilder::buildResponseHeaders(HttpElement &element)
{
	std::map<std::string, std::string> requestHeaders = element.request->headers.getAllHeaders();
	std::string connection = requestHeaders[CONNECTIONKEY] + "\r\n";
	std::string date = std::string(ctime(&this->date));
	std::string content = "*/*\r\n";
	setPair(LASTMODIFIEDKEY, MODFIEDVALUE);
	setPair(CONNECTIONKEY, connection);
	setPair(CONTENTTYPEKEY, content);
	setPair(SERVERKEY, APAACHE);
	setPair(DATEKEY, date);
	element.response->headers.setHeaders(headers);
	element.response->info.setEmptyLine(true);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseHeadersBuilder::setPair(const std::string &key, const std::string &value)
{
	headers[key] = value;
}