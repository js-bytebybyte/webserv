#include "../../../includes/Validation/Request/GetRequestHeadersValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
GetRequestHeadersValidation::GetRequestHeadersValidation(void)
{
}

GetRequestHeadersValidation::~GetRequestHeadersValidation(void)
{
}

GetRequestHeadersValidation::GetRequestHeadersValidation(const GetRequestHeadersValidation &other) : RequestHeadersValidation(other)
{
	*this = other;
}

GetRequestHeadersValidation &GetRequestHeadersValidation::operator=(const GetRequestHeadersValidation &other)
{
	(void)other;
	return (*this);
}

/*
	Function to valdiate the mandatory headers for a GET request
*/
bool GetRequestHeadersValidation::hasValidHeaders(void)
{
	if (hasSpecificKey(HOSTKEY))
		return (setValidHeaders(true), true);
	else
		return (setValidHeaders(false), false);
}