#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"
#include "RequestBodyValidation.hpp"

class PostRequestBodyValidation : public RequestBodyValidation
{
  private:
	/*
		Helper functions
	*/
	std::string getLine(const std::string &content);
	bool validateRest(std::string &content, std::string &bodyLine, HttpRequest &request);
	bool hasBody(std::string &bodyLine, HttpRequest &request);
	bool isLimiterSame(std::string &bodyLine, HttpRequest &request);
	std::string getDelimiter(std::string &boundary);
	std::string removeQuote(const std::string &str);
	void collectCgiInfo(const std::string &content, HttpRequest &request);
	void parseMultipartBody(std::string &content, std::string &bodyLine, HttpRequest &request);

  public:
	/* Cannonical form*/
	PostRequestBodyValidation(void);
	~PostRequestBodyValidation(void);
	PostRequestBodyValidation(const PostRequestBodyValidation &other);
	PostRequestBodyValidation &operator=(const PostRequestBodyValidation &other);
	bool validate(std::string &bodyLine, HttpRequest &request);
};