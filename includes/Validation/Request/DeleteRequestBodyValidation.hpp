#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "RequestBodyValidation.hpp"

class DeleteRequestBodyValidation : public RequestBodyValidation
{
  public:
	/* Cannonical form*/
	DeleteRequestBodyValidation(void);
	~DeleteRequestBodyValidation(void);
	DeleteRequestBodyValidation(const DeleteRequestBodyValidation &other);
	DeleteRequestBodyValidation &operator=(const DeleteRequestBodyValidation &other);

	/*
		Function to validate depending on what you will validate
	*/
	bool validate(std::string &bodyLine, HttpRequest &request);
};