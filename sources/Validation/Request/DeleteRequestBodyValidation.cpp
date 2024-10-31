#include "../../../includes/Validation/Request/DeleteRequestBodyValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
DeleteRequestBodyValidation::DeleteRequestBodyValidation(void)
{
}

DeleteRequestBodyValidation::~DeleteRequestBodyValidation(void)
{
}

DeleteRequestBodyValidation::DeleteRequestBodyValidation(const DeleteRequestBodyValidation &other) : RequestBodyValidation(other)
{
	*this = other;
}

DeleteRequestBodyValidation &DeleteRequestBodyValidation::operator=(const DeleteRequestBodyValidation &other)
{
	(void)other;
	return (*this);
}

/*
	Function to validate depending on what you will validate
	request line, headers, body, etc...
*/
bool DeleteRequestBodyValidation::validate(std::string &bodyLine, HttpRequest &request)
{
	// delete should not have a body
	if (bodyLine.size() > 0)
	{
		request.info.setValidRequest(false);
		request.info.setCompleteRequest(true);
		return (false);
	}
	request.info.setValidRequest(true);
	request.info.setCompleteRequest(true);
	return (true);
}