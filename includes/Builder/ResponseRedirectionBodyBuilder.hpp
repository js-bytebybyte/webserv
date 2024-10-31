#pragma once

#include "../ConfigFile/ConfigServer.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"

class ResponseRedirectionBodyBuilder
{
  private:
	/*Private variables*/
	FileHandler fileHandler;

  public:
	/* Canonical form */
	ResponseRedirectionBodyBuilder(void);
	ResponseRedirectionBodyBuilder(const ResponseRedirectionBodyBuilder &other);
	ResponseRedirectionBodyBuilder &operator=(const ResponseRedirectionBodyBuilder &other);
	~ResponseRedirectionBodyBuilder(void);

	/*
		Function to handle the response body
	*/
	void buildRedirectionResponseBody(HttpElement &element, const ConfigServer &server, const std::string &path, std::string &body);
};