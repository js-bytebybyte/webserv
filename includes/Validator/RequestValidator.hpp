#pragma once

#include "../Project.hpp"
#include "../Validation/Request/DeleteRequestBodyValidation.hpp"
#include "../Validation/Request/DeleteRequestHeadersValidation.hpp"
#include "../Validation/Request/GetRequestBodyValidation.hpp"
#include "../Validation/Request/GetRequestHeadersValidation.hpp"
#include "../Validation/Request/PostRequestBodyValidation.hpp"
#include "../Validation/Request/PostRequestHeadersValidation.hpp"
#include "../Validation/Request/RequestBodyValidation.hpp"
#include "../Validation/Request/RequestHeadersValidation.hpp"
#include "../Validation/Request/RequestLineValidation.hpp"

class RequestValidator
{
  public:
	/* Cannonical form*/
	RequestValidator(void);
	~RequestValidator(void);
	RequestValidator(const RequestValidator &other);
	RequestValidator &operator=(const RequestValidator &other);
	RequestBodyValidation *createRequestBodyValidator(const HttpRequest &httpRequest);
	RequestHeadersValidation *createRequestHeadersValidator(const HttpRequest &httpRequest);

	/*
		All the components to validate a request
	*/
	RequestLineValidation requestLineValidator;
	RequestHeadersValidation *requestHeadersValidator;
	RequestBodyValidation *requestBodyValidator;
};
