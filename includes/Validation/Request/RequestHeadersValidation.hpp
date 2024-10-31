#pragma once

#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"

class RequestHeadersValidation
{
  public:
	/*Canonical form*/
	RequestHeadersValidation(void);
	virtual ~RequestHeadersValidation(void);
	RequestHeadersValidation(const RequestHeadersValidation &other);
	RequestHeadersValidation &operator=(const RequestHeadersValidation &other);

	/*
		Function to valdiate an entire header
	*/
	bool isValidHeader(const std::string &header);

	/*
		Function to valdiate the mandatory headers for a request
	*/
	virtual bool hasValidHeaders(void) = 0;
	
	/*
		GETTERS to get the atributes of the class
	*/
	bool getValidHeaders(void) const;

	/*
		SETTERS to modify the atributes of the class
	*/
	void setSingleHeader(const std::string &name, const std::string &value);
	void setValidHeaders(bool valid);
	bool chunked;

  private:
	// hold a list with all the keys seen so far
	std::map<std::string, std::string> duplicates;
	bool validheaders;
	unsigned int status;

	/*
		Checkers for the request headers
	*/
	bool isSpecialChar(char c) const;
	bool isValidKey(const std::string &key) const;
	bool isValidValue(const std::string &value) const;
	bool isDupliacte(const std::string &key) const;

  protected:
	bool hasSpecificKey(const std::string &key) const;
};
