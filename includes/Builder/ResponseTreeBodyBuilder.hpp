#pragma once

#include "../ConfigFile/ConfigRoute.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "ResponseRedirectionBodyBuilder.hpp"

class ResponseTreeBodyBuilder
{
  private:
	/*Private variables*/
	FileHandler fileHandler;
	std::string body;
	ResponseRedirectionBodyBuilder redirectionBodyBuilder;

	/*
		Helper functions
	*/
	void buildListing(const ConfigRoute &route);
	std::vector<std::string> getListing(const std::string &directoryPath, const bool &tree);
	std::string createHtmlList(const std::vector<std::string> &list);
	std::string readImage(const ConfigRoute &route);
	bool containsWhitespace(const std::string &str);
	std::string createDeleteList(const std::vector<std::string> &list);
	void buildDeleteList(const ConfigRoute &route);

  public:
	/*Canonical form*/
	ResponseTreeBodyBuilder(void);
	ResponseTreeBodyBuilder(const ResponseTreeBodyBuilder &ref);
	ResponseTreeBodyBuilder &operator=(const ResponseTreeBodyBuilder &rhs);
	~ResponseTreeBodyBuilder(void);

	/*
		Function to handle the response body
	*/
	void buildMethodResponseBody(HttpElement &element, const ConfigRoute &route, const ConfigServer &server, bool &found);
};