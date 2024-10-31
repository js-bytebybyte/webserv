#pragma once

#include "../Http/HttpElement.hpp"
#include "../Project.hpp"

class ResponseLineBuilder
{
  private:
	/*Variables*/
	std::string http;
	unsigned int statusCode;
	std::string reason;
	std::string statusLine;

	/*
		Helper functions
	*/
	void buildHttp(void);
	void buildStatusCode(const HttpRequest &request);
	std::string buildInformational(void) const;
	std::string buildSuccess(void) const;
	std::string buildRedirection(void) const;
	std::string buildClientError(void) const;
	std::string buildServerError(void) const;
	void buildReason(void);

  public:
	/*Canonical form*/
	ResponseLineBuilder(void);
	ResponseLineBuilder(const ResponseLineBuilder &ref);
	ResponseLineBuilder &operator=(const ResponseLineBuilder &rhs);
	~ResponseLineBuilder(void);

	/*
		Function to handle the response
	*/
	void buildResponseLine(HttpElement &element);
};