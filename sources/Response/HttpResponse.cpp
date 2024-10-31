#include "../../includes/Response/HttpResponse.hpp"

// Canonical form
HttpResponse::HttpResponse(void) : info(), statusLine(), headers(), body()
{
}

HttpResponse::HttpResponse(const HttpResponse &other)
{
	*this = other;
}

HttpResponse &HttpResponse::operator=(const HttpResponse &other)
{
	if (this != &other)
	{
		info = other.info;
		statusLine = other.statusLine;
		headers = other.headers;
		body = other.body;
	}
	return (*this);
}

HttpResponse::~HttpResponse(void)
{
}
