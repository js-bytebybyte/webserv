#include "../../../includes/Parsing/Request/RequestBodyParsing.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
RequestBodyParsing::RequestBodyParsing(void)
{
}

RequestBodyParsing::~RequestBodyParsing(void)
{
}

RequestBodyParsing::RequestBodyParsing(const RequestBodyParsing &other) : RequestParsing(other)
{
	*this = other;
}

RequestBodyParsing &RequestBodyParsing::operator=(const RequestBodyParsing &other)
{
	(void)other;
	return (*this);
}
