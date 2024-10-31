#include "../../../includes/Validation/Request/RequestBodyValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
RequestBodyValidation::RequestBodyValidation(void)
{
}

RequestBodyValidation::~RequestBodyValidation(void)
{
}

RequestBodyValidation::RequestBodyValidation(const RequestBodyValidation &other)
{
	*this = other;
}

RequestBodyValidation &RequestBodyValidation::operator=(const RequestBodyValidation &other)
{
	(void)other;
	return (*this);
}

/*PROTECTED FUNCTIONS*/
bool RequestBodyValidation::hasEmptyLine(const std::string &bodyLine)
{
	if (bodyLine.compare("\r") == 0)
		return (true);
	return (false);
}

std::string RequestBodyValidation::trim(const std::string &str) const
{
	size_t start;
	size_t end;

	std::string trimmed;
	start = str.find_first_not_of(" \t\r\n");
	end = str.find_last_not_of(" \t\r\n");
	if (start == std::string::npos)
		trimmed = "";
	else
		trimmed = str.substr(start, end - start + 1);
	return (trimmed);
}
