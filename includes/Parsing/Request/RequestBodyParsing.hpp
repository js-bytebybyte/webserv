#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "RequestParsing.hpp"

class RequestBodyParsing : public RequestParsing
{
  public:
	/*Canonical form*/
	RequestBodyParsing(void);
	virtual ~RequestBodyParsing(void);
	RequestBodyParsing(const RequestBodyParsing &other);
	RequestBodyParsing &operator=(const RequestBodyParsing &other);

	/*
		Function to pasre depending on what you will parse
		request line, headers, body, etc...
	*/
	virtual void parse(HttpRequest &httpRequest) = 0;

  protected:
	/*
		Function to parse the body.
	*/
	virtual void parseBody(std::istringstream &stream, HttpRequest &request) const = 0;
};
