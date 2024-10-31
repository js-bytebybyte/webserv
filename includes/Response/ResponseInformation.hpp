#pragma once

#include "../Project.hpp"

class ResponseInformation
{
  private:
	/*Private variables*/
	std::string fullResponse;
	bool emptyLine;
	bool validResponse;
	bool completeResponse;

  public:
	/*Canonical form*/
	ResponseInformation(void);
	ResponseInformation(const std::string &raw);
	ResponseInformation(const ResponseInformation &other);
	ResponseInformation &operator=(const ResponseInformation &other);
	~ResponseInformation(void);

	/*
		Getters
	*/
	std::string getFullResponse(void) const;
	bool getEmptyLine(void) const;
	bool getValidResponse(void) const;
	bool getCompleteResponse(void) const;

	/*
		Setters
	*/
	void setFullResponse(const std::string &raw);
	void setEmptyLine(const bool &b);
	void setValidResponse(const bool &b);
	void setCompleteResponse(const bool &b);
};