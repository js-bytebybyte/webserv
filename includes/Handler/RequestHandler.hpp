#pragma once

#include "../Http/HttpElement.hpp"
#include "../Parser/ParserElement.hpp"
#include "../Project.hpp"
#include "../Request/HttpRequest.hpp"

class RequestHandler
{
  private:
	ParserElement parser;

	/*Helper functions*/
	bool chooseMethod(const std::string &request, HttpElement &element, ConfigServer &configServer);

  public:
	/*Canonical form*/
	RequestHandler(void);
	RequestHandler(const RequestHandler &other);
	RequestHandler &operator=(const RequestHandler &other);
	~RequestHandler(void);

	/*
		Function to handle the request
	*/
	bool handleRequest(const std::string &request, HttpElement &element, ConfigServer &configServer);
};