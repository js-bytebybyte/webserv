#pragma once

#include "../Project.hpp"

class HttpHeaders
{
  private:
	/*Private variables */
	std::map<std::string, std::string> headers;
	std::vector<std::string> domainsVectorServer;

  public:
	/* Cannonical form*/
	HttpHeaders(void);
	HttpHeaders(const std::map<std::string, std::string> &headers);
	HttpHeaders(const std::vector<std::string> &domains);
	HttpHeaders(const HttpHeaders &other);
	HttpHeaders &operator=(const HttpHeaders &other);
	~HttpHeaders(void);

	/*
		GETTERS to access all the atributes of the class
	*/
	std::string getSingleHeaderValueFromKey(const std::string &key) const;
	std::string getSingleHeaderKeyFromKey(const std::string &key) const;
	std::string getSingleHeaderValueFromValue(const std::string &value) const;
	std::string getSingleHeaderKeyFromValue(const std::string &value) const;
	std::map<std::string, std::string> getAllHeaders(void) const;
	std::string getHeadersString(void) const;
	std::vector<std::string> getDomainsVectorServer(void) const;

	/*
		SETTERS to modify the atributes of the class
	*/
	void setSingleHeader(const std::string &name, const std::string &value);
	void setHeaders(const std::map<std::string, std::string> &headers);
	void setDomainsVectorServer(const std::vector<std::string> &domains);
};
