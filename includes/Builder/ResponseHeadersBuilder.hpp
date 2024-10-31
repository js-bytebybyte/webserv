#pragma once

#include "../Http/HttpElement.hpp"
#include "../Project.hpp"

class ResponseHeadersBuilder
{
  private:
	/*Variables*/
	std::map<std::string, std::string> headers;
	time_t date;
	std::string currentTime;

	/*
		Helper functions
	*/
	void setPair(const std::string &key, const std::string &value);

  public:
	/*Canonical form*/
	ResponseHeadersBuilder(void);
	ResponseHeadersBuilder(const ResponseHeadersBuilder &ref);
	ResponseHeadersBuilder &operator=(const ResponseHeadersBuilder &rhs);
	~ResponseHeadersBuilder(void);

	/*
		Function to handle the response
	*/
	void buildResponseHeaders(HttpElement &element);
};