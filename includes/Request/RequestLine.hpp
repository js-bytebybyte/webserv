#pragma once

#include "../Project.hpp"

class RequestLine
{
  private:
	/*Private variables*/
	std::string requestLine;
	std::string methode;
	std::string uri;
	std::string version;

  public:
	/* Cannonical form*/
	RequestLine(void);
	RequestLine(const std::string &full, const std::string &method, const std::string &url, const std::string &http);
	RequestLine(const RequestLine &ref);
	RequestLine &operator=(const RequestLine &ref);
	~RequestLine(void);

	/*
		GETTERS to access all the atributes of the class
	*/
	std::string getFullRequestLine(void) const;
	std::string getMethode(void) const;
	std::string getUri(void) const;
	std::string getHttp(void) const;

	/*
		SETTERS to modify the atributes of the class
	*/
	void setFullRequestLine(const std::string &fullLine);
	void setMethode(const std::string &method);
	void setUri(const std::string &url);
	void setHttp(const std::string &http);
};
