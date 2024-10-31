#pragma once

#include "../ConfigFile/ConfigServer.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "../Validation/Response/ResponseValidation.hpp"

class ResponseValidator
{
  private:
	ResponseValidation _responseValidation;

  public:
	/* Cannonical form*/
	ResponseValidator(void);
	~ResponseValidator(void);
	ResponseValidator(const ResponseValidator &other);
	ResponseValidator &operator=(const ResponseValidator &other);

	bool checker(HttpRequest &request, ConfigServer &cfg);
	ResponseValidation getValidator(void) const;

	/*
		All the components to validate a request
	*/
	int status_code;
};
