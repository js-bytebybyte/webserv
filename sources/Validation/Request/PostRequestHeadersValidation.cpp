#include "../../../includes/Validation/Request/PostRequestHeadersValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
PostRequestHeadersValidation::PostRequestHeadersValidation(void)
{
}

PostRequestHeadersValidation::~PostRequestHeadersValidation(void)
{
}

PostRequestHeadersValidation::PostRequestHeadersValidation(const PostRequestHeadersValidation &other) : RequestHeadersValidation(other)
{
	*this = other;
}

PostRequestHeadersValidation &PostRequestHeadersValidation::operator=(const PostRequestHeadersValidation &other)
{
	(void)other;
	return (*this);
}

/*
	Function to valdiate the mandatory headers for a POST request
*/
bool PostRequestHeadersValidation::hasValidHeaders(void)
{
	if (chunked && hasSpecificKey(HOSTKEY) && hasSpecificKey(CONTENTTYPEKEY))
		return (setValidHeaders(true), true);
	else if (hasSpecificKey(HOSTKEY) && hasSpecificKey(CONTENTTYPEKEY) && hasSpecificKey(CONTENTLENGTHKEY))
		return (setValidHeaders(true), true);
	else
		return (setValidHeaders(false), false);
}
