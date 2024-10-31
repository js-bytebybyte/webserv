#pragma once

#include "../ConfigFile/ConfigServer.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "../Validation/Response/ResponseValidation.hpp"
#include "ResponseErrorBodyBuilder.hpp"
#include "ResponseMethodBodyBuilder.hpp"

class ResponseBodyBuilder
{
  private:
	/*Private variables*/
	std::string body;
	bool found;
	FileHandler fileHandler;
	ResponseMethodBodyBuilder methodBodyBuilder;
	ResponseErrorBodyBuilder errorBodyBuilder;

	/*
		Helper functions
	*/
	void contentLength(const HttpElement &element);
	void buildCgiResponseBody(HttpElement &element, const ConfigServer &server);
	bool isCgi(const int &choise, const std::string &uri);
	void checkForCgi(HttpElement &element, const ConfigServer &server, const int &choise, bool &cgiFlag, const std::string &uri,
		const std::string &filePath);
	std::string trim(const std::string &str) const;
	void transcribeBody(const std::string &filePath, const std::string &endBody);
	void preparePostBody(HttpElement &element, std::string &filePath, const ConfigServer &server, ResponseValidation &responseValidation);
	void prepareDeleteBody(HttpElement &element, int &choise, const std::string &uri);

  public:
	/*Canonical form*/
	ResponseBodyBuilder(void);
	ResponseBodyBuilder(const ResponseBodyBuilder &ref);
	ResponseBodyBuilder &operator=(const ResponseBodyBuilder &rhs);
	~ResponseBodyBuilder(void);

	/*
		Function to handle the response
	*/
	void buildResponseBody(HttpElement &element, const ConfigServer &server, int &choise, ResponseValidation &responseValidation);
	void buildErrorResponseBody(HttpElement &element, const ConfigServer &server, const bool &fallback);
};