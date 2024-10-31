#pragma once

#include "../Parsing/Request/DeleteRequestBodyParsing.hpp"
#include "../Parsing/Request/GetRequestBodyParsing.hpp"
#include "../Parsing/Request/PostRequestBodyParsing.hpp"
#include "../Parsing/Request/RequestBodyParsing.hpp"
#include "../Parsing/Request/RequestHeadersParsing.hpp"
#include "../Parsing/Request/RequestLineParsing.hpp"
#include "../Project.hpp"
#include "../Request/HttpRequest.hpp"

class RequestParser
{
  private:
	/*
		All the components that are needed to parse the request
	*/
	RequestLineParsing requestLineParser;
	RequestHeadersParsing headersParser;
	RequestBodyParsing *bodyParser;

	/*
		Helper functions
	*/
	RequestBodyParsing *selectBodyParser(const HttpRequest &request);
	void parsingError(HttpRequest &httpRequest);

  public:
	/*Canonical form*/
	RequestParser(void);
	~RequestParser(void);
	RequestParser(const RequestParser &other);
	RequestParser &operator=(const RequestParser &other);

	/*
		Function to parse the entire request
	*/
	void parseRequest(HttpRequest &httpRequest);
};
