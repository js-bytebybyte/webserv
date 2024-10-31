#pragma once

#include "../../Project.hpp"
#include "RequestBodyParsing.hpp"

class PostRequestBodyParsing : public RequestBodyParsing
{
  private:
	/*
		Helper functions
	*/
	void parseRemainingContent(std::istringstream &stream, HttpRequest &request) const;
	void parseBody(std::istringstream &stream, HttpRequest &request) const;
	void unchunkBody(std::istringstream &stream, HttpRequest &request) const;

  public:
	/* Cannonical form*/
	PostRequestBodyParsing(void);
	virtual ~PostRequestBodyParsing(void);
	PostRequestBodyParsing(const PostRequestBodyParsing &other);
	PostRequestBodyParsing &operator=(const PostRequestBodyParsing &other);

	/*
		Function to pasre depending on what you will parse
	*/
	virtual void parse(HttpRequest &httpRequest);
};