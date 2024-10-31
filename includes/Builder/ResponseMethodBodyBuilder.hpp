#pragma once

#include "../ConfigFile/ConfigServer.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "ResponseTreeBodyBuilder.hpp"

class ResponseMethodBodyBuilder
{
  private:
	/*Private variables*/
	ResponseTreeBodyBuilder treeBodyBuilder;

	/*
		Helper functions
	*/
	void buildGetResponseBody(HttpElement &element, const ConfigServer &server, const size_t &location, bool &found);
	void buildDeleteResponseBody(HttpElement &element, const ConfigServer &server, const size_t &location, bool &found);
	char hexToChar(const std::string &hex);
	std::string decodeUrl(const std::string &input);
	bool existsFile(const std::string &filename);
	void deleteFile(HttpElement &element, const size_t &location, const ConfigServer &server);

  public:
	/*Canonical form*/
	ResponseMethodBodyBuilder(void);
	ResponseMethodBodyBuilder(const ResponseMethodBodyBuilder &ref);
	ResponseMethodBodyBuilder &operator=(const ResponseMethodBodyBuilder &rhs);
	~ResponseMethodBodyBuilder(void);

	/*
		Function to handle the response body
	*/
	void buildMethodResponseBody(HttpElement &element, const ConfigServer &server, const int &location, bool &found,
		int &choise);
};