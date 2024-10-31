#include "../../includes/Validator/RequestValidator.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
RequestValidator::RequestValidator(void) : requestLineValidator(), requestHeadersValidator(NULL), requestBodyValidator(NULL)
{
}

RequestValidator::RequestValidator(const RequestValidator &other)
{
	*this = other;
}

RequestValidator &RequestValidator::operator=(const RequestValidator &other)
{
	if (this != &other)
	{
		requestLineValidator = other.requestLineValidator;
		requestHeadersValidator = other.requestHeadersValidator;
		requestBodyValidator = other.requestBodyValidator;
	}
	return (*this);
}

RequestValidator::~RequestValidator(void)
{
	if (requestHeadersValidator)
		delete requestHeadersValidator;
	if (requestBodyValidator)
		delete requestBodyValidator;
}

RequestBodyValidation *RequestValidator::createRequestBodyValidator(const HttpRequest &httpRequest)
{
	std::string method = httpRequest.requestLine.getMethode();
	if (method == "GET")
		return (new GetRequestBodyValidation());
	else if (method == "POST")
		return (new PostRequestBodyValidation());
	else if (method == "DELETE")
		return (new DeleteRequestBodyValidation());
	else
		return (NULL);
}

RequestHeadersValidation *RequestValidator::createRequestHeadersValidator(const HttpRequest &httpRequest)
{
	std::string method = httpRequest.requestLine.getMethode();
	if (method == "GET")
		return (new GetRequestHeadersValidation());
	else if (method == "POST")
		return (new PostRequestHeadersValidation());
	else if (method == "DELETE")
		return (new DeleteRequestHeadersValidation());
	else
		return (NULL);
}