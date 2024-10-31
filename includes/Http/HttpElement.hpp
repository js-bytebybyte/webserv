#pragma once

#include "../Project.hpp"
#include "../Request/HttpRequest.hpp"
#include "../Response/HttpResponse.hpp"
#include "HttpConfig.hpp"

// class HttpResponse;
class HttpElement
{
  public:
	/* Cannonical form*/
	HttpElement(void);
	HttpElement(const HttpElement &other);
	HttpElement &operator=(const HttpElement &other);
	~HttpElement(void);

	/*
		All the main components that are needed in the project
	*/
	char *rBuff;
	HttpRequest *request;
	HttpResponse *response;
};
