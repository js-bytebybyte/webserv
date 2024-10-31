#pragma once

#include "../../Project.hpp"
#include "RequestBodyParsing.hpp"

class DeleteRequestBodyParsing : public RequestBodyParsing
{
  private:
	/*
		Function to parse the body.
	*/
	void parseBody(std::istringstream &stream, HttpRequest &request) const;

  public:
	/* Cannonical form*/
	DeleteRequestBodyParsing(void);
	virtual ~DeleteRequestBodyParsing(void);
	DeleteRequestBodyParsing(const DeleteRequestBodyParsing &other);
	DeleteRequestBodyParsing &operator=(const DeleteRequestBodyParsing &other);

	/*
		Function to pasre depending on what you will parse
	*/
	virtual void parse(HttpRequest &httpRequest);
};
