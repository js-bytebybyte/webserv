#pragma once

#include "../ConfigFile/ConfigServer.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"

class ResponseErrorBodyBuilder
{
  private:
	/*Private variables*/
	int errorPage;
	int errorIndex;
	FileHandler fileHandler;
	std::string body;

	/*
		Helper functions
	*/
	void findLocation(const HttpElement &element, const ConfigServer &server, const int &error);
	void buildError(const HttpElement &element, const ConfigServer &server);

  public:
	/*Canonical form*/
	ResponseErrorBodyBuilder(void);
	ResponseErrorBodyBuilder(const ResponseErrorBodyBuilder &ref);
	ResponseErrorBodyBuilder &operator=(const ResponseErrorBodyBuilder &rhs);
	~ResponseErrorBodyBuilder(void);

	/*
		Function to handle the response
	*/
	void buildErrorResponseBody(HttpElement &element, const ConfigServer &server);
	void buildFallBackErrorBody(HttpElement &element);
};