#pragma once

#include "../Builder/ResponseBodyBuilder.hpp"
#include "../Builder/ResponseHeadersBuilder.hpp"
#include "../Builder/ResponseLineBuilder.hpp"
#include "../ConfigFile/ConfigServer.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "../Validator/ResponseValidator.hpp"

class ResponseHandler
{
  private:
	FileHandler fileHandler;
	ResponseLineBuilder responseLineBuilder;
	ResponseHeadersBuilder responseHeadersBuilder;
	ResponseBodyBuilder responseBodyBuilder;
	ResponseValidator _validator;

	/*
		Helper functions
	*/
	void buildFullResponse(HttpElement &element);
	void codeBuilder(int &code, int &choice, HttpElement &element,
		const ConfigServer &server);

  public:
	/*Canonical form*/
	ResponseHandler(void);
	ResponseHandler(const ResponseHandler &ref);
	ResponseHandler &operator=(const ResponseHandler &rhs);
	~ResponseHandler(void);

	/*
		Function to handle the response
	*/
	void handleResponse(int &choise, HttpElement &element,
		ConfigServer &server);
	void handleError(HttpElement &element, const std::string &error,
		const unsigned int &status);

	/*Setters*/
	int setMethod(HttpRequest &request);
	void setValidator(ResponseValidator &rp);
};