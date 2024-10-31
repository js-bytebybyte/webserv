#include "../../../includes/Validation/Request/DeleteRequestHeadersValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
DeleteRequestHeadersValidation::DeleteRequestHeadersValidation(void)
{
}

DeleteRequestHeadersValidation::~DeleteRequestHeadersValidation(void)
{
}

DeleteRequestHeadersValidation::DeleteRequestHeadersValidation(const DeleteRequestHeadersValidation &other) : RequestHeadersValidation(other)
{
	*this = other;
}

DeleteRequestHeadersValidation &DeleteRequestHeadersValidation::operator=(const DeleteRequestHeadersValidation &other)
{
	(void)other;
	return (*this);
}

/*
	Function to valdiate the mandatory headers for a DELETE request
*/
// look for the mandatory headers for a DELETE request
bool DeleteRequestHeadersValidation::hasValidHeaders(void)
{
	if (hasSpecificKey(HOSTKEY))
		return (setValidHeaders(true), true);
	else
		return (setValidHeaders(false), false);
}