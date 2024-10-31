#pragma once

#include "../../Project.hpp"
#include "RequestBodyParsing.hpp"

class GetRequestBodyParsing : public RequestBodyParsing
{
  protected:
	/*
		Function to parse the body.
	*/
	void parseBody(std::istringstream &stream, HttpRequest &request) const;

  public:
	/* Cannonical form*/
	GetRequestBodyParsing(void);
	virtual ~GetRequestBodyParsing(void);
	GetRequestBodyParsing(const GetRequestBodyParsing &other);
	GetRequestBodyParsing &operator=(const GetRequestBodyParsing &other);

	/*
		Function to pasre depending on what you will parse
	*/
	virtual void parse(HttpRequest &httpRequest);
};