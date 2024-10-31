#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "../../Request/RequestLine.hpp"
#include "RequestParsing.hpp"

class RequestLineParsing : public RequestParsing
{
  private:
	/*
		Helper function to parse the request line
	*/
	RequestLine parseRequestLine(const std::string &line);

  public:
	/*Canonical form*/
	RequestLineParsing(void);
	virtual ~RequestLineParsing(void);
	RequestLineParsing(const RequestLineParsing &other);
	RequestLineParsing &operator=(const RequestLineParsing &other);

	/*
		Function to pasre depending on what you will parse
	*/
	virtual void parse(HttpRequest &httpRequest);
};
