#pragma once

#include "../CGI/CgiHandler.hpp"
#include "../Http/HttpBody.hpp"
#include "../Http/HttpHeaders.hpp"
#include "../Project.hpp"
#include "RequestInformation.hpp"
#include "RequestLine.hpp"

class HttpRequest
{
  public:
	/*Canonical form*/
	HttpRequest(void);
	HttpRequest(const std::string &raw, const std::vector<std::string> &domains);
	HttpRequest(const HttpRequest &other);
	HttpRequest &operator=(const HttpRequest &other);
	~HttpRequest(void);

	/*
		All the elements that are convay information about the request
	*/
	RequestInformation info;
	RequestLine requestLine;
	HttpHeaders headers;
	HttpBody body;
	CgiHandler cgiHandler;
};
