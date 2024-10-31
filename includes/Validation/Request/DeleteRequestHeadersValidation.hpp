#pragma once

#include "../../Project.hpp"
#include "RequestHeadersValidation.hpp"

class DeleteRequestHeadersValidation : public RequestHeadersValidation
{
  public:
	/*Canonical form*/
	DeleteRequestHeadersValidation(void);
	virtual ~DeleteRequestHeadersValidation(void);
	DeleteRequestHeadersValidation(const DeleteRequestHeadersValidation &other);
	DeleteRequestHeadersValidation &operator=(const DeleteRequestHeadersValidation &other);

	/*
		Function to valdiate the mandatory headers for a DELETE request
	*/
	bool hasValidHeaders(void);
};