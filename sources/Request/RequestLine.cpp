#include "../../includes/Request/RequestLine.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
RequestLine::RequestLine(void) : requestLine("NULL"), methode("NULL"), uri("NULL"), version("NULL")
{
}

RequestLine::RequestLine(const std::string &raw, const std::string &method, const std::string &url, const std::string &http) : requestLine(raw), methode(method), uri(url), version(http)
{
}

RequestLine::RequestLine(const RequestLine &ref)
{
	*this = ref;
}

RequestLine &RequestLine::operator=(const RequestLine &ref)
{
	if (this != &ref)
	{
		requestLine = ref.requestLine;
		methode = ref.methode;
		uri = ref.uri;
		version = ref.version;
	}
	return (*this);
}

RequestLine::~RequestLine(void)
{
}

/*
	GETTERS to access all the atributes of the class
*/

std::string RequestLine::getFullRequestLine(void) const
{
	return (requestLine);
}

std::string RequestLine::getMethode(void) const
{
	return (methode);
}

std::string RequestLine::getUri() const
{
	return (uri);
}

std::string RequestLine::getHttp() const
{
	return (version);
}

/*
	SETTERS to modify the atributes of the class
*/
void RequestLine::setFullRequestLine(const std::string &fullLine)
{
	requestLine = fullLine;
}

void RequestLine::setMethode(const std::string &method)
{
	methode = method;
}

void RequestLine::setUri(const std::string &url)
{
	uri = url;
}

void RequestLine::setHttp(const std::string &http)
{
	version = http;
}
