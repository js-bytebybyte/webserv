#include "../../../includes/Validation/Request/RequestLineValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Canonical form */
RequestLineValidation::RequestLineValidation(void) : status(OK)
{
}

RequestLineValidation::~RequestLineValidation(void)
{
}

RequestLineValidation::RequestLineValidation(const RequestLineValidation &other)
{
	*this = other;
}

RequestLineValidation &RequestLineValidation::operator=(const RequestLineValidation &other)
{
	(void)other;
	return (*this);
}

/*
	Function to valdiate the entire request line
*/
bool RequestLineValidation::isValidRequestLine(const std::vector<std::string> &parts)
{
	if (parts.size() != 3)
		return (false);
	std::string method = parts[0];
	std::string uri = parts[1];
	std::string version = parts[2];
	return (isValidMethod(method) && isValidUri(uri) && isValidVersion(version));
}

/*PRIVATE FUNCTIONS*/

/*
		Checkers for the request line:
*/
bool RequestLineValidation::isValidMethod(const std::string &method)
{
	int		lastElement;
	bool	inside;

	// list of valid methods
	std::string validMethodsList[] = {"GET", "POST", "DELETE"};
	// calculate the size of the array
	lastElement = sizeof(validMethodsList) / sizeof(std::string);
	std::string *validMethodsEnd = validMethodsList + lastElement;
	// create a vector with the valid methods
	std::vector<std::string> validMethods(validMethodsList, validMethodsEnd);
	// check if the method is in the list of valid methods
	inside = (std::find(validMethods.begin(), validMethods.end(), method) != validMethods.end());
	if (!inside)
		status = METHOD_NOT_ALLOWED;
	return (inside);
}

bool RequestLineValidation::isValidUri(const std::string &uri)
{
	return (!uri.empty() && uri[0] == '/');
}

/*
	Check if the version is valid
	split the version into its components
	and check if each component is valid
*/
bool RequestLineValidation::isValidVersion(const std::string &version)
{
	if (version.size() != 8)
	{
		status = BAD_REQUEST;
		return (false);
	}
	// check if the version starts with "HTTP/" or if the version has a dot
	if (version.substr(0, 5) != "HTTP/" && version[6] != '.')
	{
		status = BAD_REQUEST;
		return (false);
	}
	// check if the version is 1.0 or 1.1 or 2.0
	if ((version[5] < '0' || version[5] > '2') && (version[7] < '0' || version[7] > '2'))
	{
		status = HTTP_VERSION_NOT_SUPPORTED;
		return (false);
	}
	return (true);
}
