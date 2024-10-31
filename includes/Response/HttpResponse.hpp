#pragma once

#include "../Http/HttpBody.hpp"
#include "../Http/HttpHeaders.hpp"
#include "../Project.hpp"
#include "ResponseInformation.hpp"
#include "ResponseLine.hpp"

class HttpResponse
{
  public:
	/*Canonical from*/
	HttpResponse(void);
	HttpResponse(const std::string &raw);
	HttpResponse(const HttpResponse &other);
	HttpResponse &operator=(const HttpResponse &other);
	~HttpResponse(void);

	/*
		Objects containing the info about the response
	*/
	ResponseInformation info;
	ResponseLine statusLine;
	HttpHeaders headers;
	HttpBody body;
};
