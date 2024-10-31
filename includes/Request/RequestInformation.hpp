#pragma once

#include "../Project.hpp"

class RequestInformation
{
  private:
	/*Private variables*/
	std::string full;
	unsigned int status;

	// Stores if there is an empty line between the headers and the body
	bool emptyLine;

	// stores if the request is valid
	bool validRequest;

	// store if the request is parsed completely
	bool completeRequest;

	// store if the request is chunked
	bool chunked;

	char *rBuff;

  public:
	/*Canonical form*/
	RequestInformation(void);
	RequestInformation(const std::string &raw);
	RequestInformation(const RequestInformation &other);
	RequestInformation &operator=(const RequestInformation &other);
	~RequestInformation(void);

	/*
		Getters
	*/
	std::string getFullRequest(void) const;
	unsigned int getStatus(void) const;
	bool getEmptyLine(void) const;
	bool getValidRequest(void) const;
	bool getCompleteRequest(void) const;
	bool getChunked(void) const;
	char *getrBuff(void) const;

	/*
		Setters
	*/
	void setFullRequest(const std::string &raw);
	void setStatus(const unsigned int &s);
	void setEmptyLine(const bool &b);
	void setValidRequest(const bool &b);
	void setCompleteRequest(const bool &b);
	void setChunked(const bool &b);
	void setrBuff(const char *buff);
};
