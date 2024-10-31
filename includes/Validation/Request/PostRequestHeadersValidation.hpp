#pragma once

#include "../../Project.hpp"
#include "RequestHeadersValidation.hpp"

class PostRequestHeadersValidation : public RequestHeadersValidation
{
  public:
	/*Canonical form*/
	PostRequestHeadersValidation(void);
	virtual ~PostRequestHeadersValidation(void);
	PostRequestHeadersValidation(const PostRequestHeadersValidation &other);
	PostRequestHeadersValidation &operator=(const PostRequestHeadersValidation &other);

	/*
		Function to valdiate the mandatory headers for a POST request
	*/
	bool hasValidHeaders(void);
};