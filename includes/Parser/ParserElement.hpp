#pragma once

#include "../Project.hpp"
#include "ConfigParser.hpp"
#include "RequestParser.hpp"

class ParserElement
{
  public:
	/* Cannonical form*/
	ParserElement(void);
	ParserElement(const ParserElement &other);
	ParserElement &operator=(const ParserElement &other);
	~ParserElement(void);

	/*
		All the elements that are capable of parsing something
	*/
	RequestParser requestParser;
	ConfigParser configParser;

	/*
		Function to print an error message
	*/
	void printError(const std::string &message) const;
};
