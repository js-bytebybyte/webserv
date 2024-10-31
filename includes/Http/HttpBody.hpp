#pragma once

#include "../Project.hpp"

class HttpBody
{
  private:
	/*Private variables */
	std::string body;
	std::string endBody;

  public:
	/* Cannonical form*/
	HttpBody(void);
	HttpBody(const HttpBody &other);
	HttpBody &operator=(const HttpBody &other);
	~HttpBody(void);

	/*
		GETTERS & SETTERS
	*/
	std::string getBody(void) const;
	std::string getEndBody(void) const;
	void setBody(const std::string &content);
	void setEndBody(const std::string &end);
};
