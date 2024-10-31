#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "../../Validator/RequestValidator.hpp"

class RequestParsing
{
  public:
	/* Cannonical form*/
	RequestParsing(void);
	virtual ~RequestParsing(void);
	RequestParsing(const RequestParsing &other);
	RequestParsing &operator=(const RequestParsing &other);

	// Abstract method to parse different parts of the request
	virtual void parse(HttpRequest &httpRequest) = 0;

	RequestValidator requestValidator;

  protected:
	/*
		Helper function to trim whitespace from both ends of a string
	*/
	std::string trim(const std::string &s) const;

	/*
		Function to split a string by a delimiter this one is assinged by limit
	*/
	std::vector<std::string> split(const std::string &str, char limit) const;
};
