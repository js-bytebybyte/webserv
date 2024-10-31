#include "../../includes/Handler/RequestHandler.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
RequestHandler::RequestHandler(void) : parser()
{
}

RequestHandler::RequestHandler(const RequestHandler &other)
{
	*this = other;
}

RequestHandler &RequestHandler::operator=(const RequestHandler &other)
{
	if (this != &other)
		parser = other.parser;
	return (*this);
}

RequestHandler::~RequestHandler(void)
{
}

/*
	Function to handle the request
*/
bool RequestHandler::handleRequest(const std::string &request, HttpElement &element, ConfigServer &configServer)
{
	//print the request to handle
	if (!chooseMethod(request, element, configServer))
		return (false);
	element.request->info.setStatus(OK);
	parser.requestParser.parseRequest(*element.request);
	return (true);
}

/*PRIVATE FUNCTIONS*/

/*Helper functions*/
bool RequestHandler::chooseMethod(const std::string &request, HttpElement &element, ConfigServer &configServer)
{
	std::string line;
	std::istringstream stream(request);
	std::getline(stream, line);

	if(element.request)
	{
		delete element.request;
		element.request = NULL;
	}
	if (line.empty())
	{
		element.request = new HttpRequest(request, configServer.domainsVector);
		return (false);
	}
	else if (line.find("GET") != std::string::npos)
		element.request = new HttpRequest(request, configServer.domainsVector);
	else if (line.find("POST") != std::string::npos)
		element.request = new HttpRequest(request, configServer.domainsVector);
	else if (line.find("DELETE") != std::string::npos)
		element.request = new HttpRequest(request, configServer.domainsVector);
	else
		element.request = new HttpRequest(request, configServer.domainsVector);
	return (true);
}