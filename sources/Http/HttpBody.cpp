#include "../../includes/Http/HttpBody.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/

HttpBody::HttpBody(void) : body("NULL"), endBody()
{
}

HttpBody::HttpBody(const HttpBody &other)
{
	*this = other;
}

HttpBody &HttpBody::operator=(const HttpBody &other)
{
	if (this != &other)
	{
		body = other.body;
		endBody = other.endBody;
	}
	return (*this);
}

HttpBody::~HttpBody(void)
{
}

/*
	Getters
*/

std::string HttpBody::getBody(void) const
{
	return (body);
}

std::string HttpBody::getEndBody(void) const
{
	return (endBody);
}

/*
	Setters
*/
void HttpBody::setBody(const std::string &content)
{
	body = content;
}
void HttpBody::setEndBody(const std::string &end)
{
	endBody = end;
}