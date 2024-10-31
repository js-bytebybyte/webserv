#include "../../includes/Request/HttpRequest.hpp"

// Canonical form
HttpRequest::HttpRequest(void) : info(), requestLine(), headers(), body(),
	cgiHandler()
{
}

HttpRequest::HttpRequest(const std::string &raw, const std::vector<std::string> &domains) : info(raw), requestLine(), headers(domains), body(),
	cgiHandler()
{
}

HttpRequest::HttpRequest(const HttpRequest &other)
{
	*this = other;
}

HttpRequest &HttpRequest::operator=(const HttpRequest &other)
{
	if (this != &other)
	{
		info = other.info;
		requestLine = other.requestLine;
		headers = other.headers;
		body = other.body;
		cgiHandler = other.cgiHandler;
	}
	return (*this);
}

HttpRequest::~HttpRequest(void)
{
}
