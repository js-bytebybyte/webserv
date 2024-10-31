#include "../../includes/Http/HttpElement.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
HttpElement::HttpElement(void) : rBuff(), request(), response()
{
}

HttpElement::HttpElement(const HttpElement &other)
{
	*this = other;
}

HttpElement &HttpElement::operator=(const HttpElement &other)
{
	if (this != &other)
	{
		rBuff = other.rBuff;
		request = other.request;
		response = other.response;
	}
	return (*this);
}

HttpElement::~HttpElement(void)
{
	if (request)
		delete request;
	if (response)
		delete response;
}
