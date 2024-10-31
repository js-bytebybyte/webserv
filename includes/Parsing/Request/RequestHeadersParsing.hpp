#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "RequestParsing.hpp"

class RequestHeadersParsing : public RequestParsing
{
  private:
	/*
		Function to parse a single header
	*/
	void parseSingleHeader(const std::string &line, HttpRequest &request);
	bool checkDomainNameWithHostHeader(HttpRequest &request);

  public:
	/*Canonical form*/
	RequestHeadersParsing(void);
	virtual ~RequestHeadersParsing(void);
	RequestHeadersParsing(const RequestHeadersParsing &other);
	RequestHeadersParsing &operator=(const RequestHeadersParsing &other);

	/*
		Function to pasre depending on what you will parse
	*/
	virtual void parse(HttpRequest &httpRequest);
};
