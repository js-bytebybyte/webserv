#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "RequestBodyValidation.hpp"

class GetRequestBodyValidation : public RequestBodyValidation
{
  public:
	/* Cannonical form*/
	GetRequestBodyValidation(void);
	~GetRequestBodyValidation(void);
	GetRequestBodyValidation(const GetRequestBodyValidation &other);
	GetRequestBodyValidation &operator=(const GetRequestBodyValidation &other);

	/*
		Function to validate depending on what you will validate
	*/
	bool validate(std::string &bodyLine, HttpRequest &request);
};