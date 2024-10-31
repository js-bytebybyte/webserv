#include "../../includes/Http/HttpHeaders.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
HttpHeaders::HttpHeaders(void) : headers(), domainsVectorServer()
{
}

HttpHeaders::HttpHeaders(const std::map<std::string, std::string> &headers) : headers(headers), domainsVectorServer()
{
}

HttpHeaders::HttpHeaders(const std::vector<std::string> &domains) : headers(), domainsVectorServer(domains)
{
}

HttpHeaders::HttpHeaders(const HttpHeaders &ref)
{
	*this = ref;
}

HttpHeaders &HttpHeaders::operator=(const HttpHeaders &ref)
{
	if (this != &ref)
	{
		this->headers = ref.headers;
		this->domainsVectorServer = ref.domainsVectorServer;
	}
	return (*this);
}

HttpHeaders::~HttpHeaders(void)
{
}

/*
	GETTERS to access all the atributes of the class
*/
std::string HttpHeaders::getSingleHeaderValueFromKey(const std::string &key) const
{
	std::map<std::string, std::string>::const_iterator it = headers.find(key);
	std::string value; // you want to retrun the second element of the pair

	if (it != headers.end())
		value = it->second;
	else
		value = "";
	return (value);
}

std::string HttpHeaders::getSingleHeaderKeyFromKey(const std::string &key) const
{
	std::map<std::string, std::string>::const_iterator it = headers.find(key);
	std::string value; // you want to retrun the first element of the pair
	if (it != headers.end())
		value = it->first;
	else
		value = "";
	return (value);
}

std::string HttpHeaders::getSingleHeaderValueFromValue(const std::string &value) const
{
	for (std::map<std::string,
		std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
	{
		if (it->second == value)
			return (it->second);
	}
	return ("");
}

std::string HttpHeaders::getSingleHeaderKeyFromValue(const std::string &value) const
{
	for (std::map<std::string,
		std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
	{
		if (it->second == value)
			return (it->first);
	}
	return ("");
}

std::map<std::string, std::string> HttpHeaders::getAllHeaders(void) const
{
	return (headers);
}

std::string HttpHeaders::getHeadersString(void) const
{
	std::string headersString;
	for (std::map<std::string,
		std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
		headersString += it->first + " " + it->second;
	headersString += "\r\n";
	return (headersString);
}

std::vector<std::string> HttpHeaders::getDomainsVectorServer(void) const
{
	return (domainsVectorServer);
}

/*
	SETTERS to modify the atributes of the class
*/
void HttpHeaders::setSingleHeader(const std::string &name,
	const std::string &value)
{
	headers[name] = value;
}

void HttpHeaders::setHeaders(const std::map<std::string, std::string> &headers)
{
	this->headers = headers;
}

void HttpHeaders::setDomainsVectorServer(const std::vector<std::string> &domains)
{
	this->domainsVectorServer = domains;
}