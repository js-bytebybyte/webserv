#pragma once

#include "../Project.hpp"

class ResponseLine
{
  private:
	/*Private variables*/
	std::string fullStatus;
	std::string http;
	unsigned int statusCode;
	std::string reason;

  public:
	/*Canonical form*/
	ResponseLine(void);
	ResponseLine(const ResponseLine &other);
	ResponseLine &operator=(const ResponseLine &other);
	~ResponseLine(void);

	/*Getters*/
	std::string getFullStatus(void) const;
	std::string getHttp(void) const;
	unsigned int getStatusCode(void) const;
	std::string getReason(void) const;

	/*Setters*/
	void setFullStatus(const std::string &full);
	void setHttp(const std::string &http);
	void setStatusCode(const unsigned int &status);
	void setReason(const std::string &reason);
};