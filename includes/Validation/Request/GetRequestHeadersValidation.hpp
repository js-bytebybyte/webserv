#pragma once

#include "../../Project.hpp"
#include "RequestHeadersValidation.hpp"

class GetRequestHeadersValidation : public RequestHeadersValidation
{
  public:
	/*Canonical form*/
	GetRequestHeadersValidation(void);
	virtual ~GetRequestHeadersValidation(void);
	GetRequestHeadersValidation(const GetRequestHeadersValidation &other);
	GetRequestHeadersValidation &operator=(const GetRequestHeadersValidation &other);

	/*
		Function to valdiate the mandatory headers for a GET request
	*/
	bool hasValidHeaders(void);
};
