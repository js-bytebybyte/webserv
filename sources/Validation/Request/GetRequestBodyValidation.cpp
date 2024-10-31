#include "../../../includes/Validation/Request/GetRequestBodyValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
GetRequestBodyValidation::GetRequestBodyValidation(void)
{
}

GetRequestBodyValidation::~GetRequestBodyValidation(void)
{
}

GetRequestBodyValidation::GetRequestBodyValidation(const GetRequestBodyValidation &other) : RequestBodyValidation(other)
{
	*this = other;
}

GetRequestBodyValidation &GetRequestBodyValidation::operator=(const GetRequestBodyValidation &other)
{
	(void)other;
	return (*this);
}

bool GetRequestBodyValidation::validate(std::string &bodyLine, HttpRequest &request)
{
	// get should not have a body
	if (bodyLine.size() > 0)
	{
		request.info.setValidRequest(false);
		request.info.setCompleteRequest(true);
		request.info.setStatus(BAD_REQUEST);
		return (false);
	}
	request.info.setValidRequest(true);
	request.info.setCompleteRequest(true);
	return (true);
}
