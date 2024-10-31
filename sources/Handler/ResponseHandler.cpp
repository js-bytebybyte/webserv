#include "../../includes/Handler/ResponseHandler.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseHandler::ResponseHandler(void) : fileHandler(), responseLineBuilder(), responseHeadersBuilder(), responseBodyBuilder(),
	_validator()
{
}

ResponseHandler::ResponseHandler(const ResponseHandler &other)
{
	*this = other;
}

ResponseHandler &ResponseHandler::operator=(const ResponseHandler &other)
{
	if (this != &other)
	{
		fileHandler = other.fileHandler;
		responseLineBuilder = other.responseLineBuilder;
		responseHeadersBuilder = other.responseHeadersBuilder;
		responseBodyBuilder = other.responseBodyBuilder;
		_validator = other._validator;
	}
	return (*this);
}

ResponseHandler::~ResponseHandler(void)
{
}

/*
	Function to handle the response
*/
void ResponseHandler::handleResponse(int &choice, HttpElement &element, ConfigServer &server)
{
	int	code;

	if(!element.request)
		element.request = new HttpRequest();
	if(!element.response)
		element.response = new HttpResponse();
	if (!element.response)
	{
		std::cout << "no RESPONSE \n";
		return ;
	}
	element.request->info.setStatus(OK);
	code = element.request->info.getStatus();
	if (code == OK)
	{
		_validator.checker(*element.request, server);
		code = element.request->info.getStatus();
	}
	codeBuilder(code, choice, element, server);
	buildFullResponse(element);
}

void ResponseHandler::codeBuilder(int &code, int &choice, HttpElement &element,
	const ConfigServer &server)
{
	int					newCode;
	ResponseValidation	validate;

	responseLineBuilder.buildResponseLine(element);
	responseHeadersBuilder.buildResponseHeaders(element);
	if (code == NOT_ACCEPTABLE)
		responseBodyBuilder.buildErrorResponseBody(element, server, true);
	if (BAD_REQUEST <= code && code <= NETWORK_AUTHENTICATION_REQUIRED)
		responseBodyBuilder.buildErrorResponseBody(element, server, false);
	else
	{
		validate = _validator.getValidator();
		responseBodyBuilder.buildResponseBody(element, server, choice, validate);
	}
	// check for redrecition && CGI failure
	newCode = element.request->info.getStatus();
	if (newCode != code)
	{
		responseLineBuilder.buildResponseLine(element);
		if (newCode == BAD_GATEWAY)
			responseBodyBuilder.buildErrorResponseBody(element, server, false);
	}
}

void ResponseHandler::handleError(HttpElement &element,
	const std::string &error, const unsigned int &status)
{
	std::string body = fileHandler.read(error, false);
	element.request = new HttpRequest();
	element.response = new HttpResponse();
	element.request->info.setStatus(status);
	responseLineBuilder.buildResponseLine(element);
	responseHeadersBuilder.buildResponseHeaders(element);
	element.response->body.setBody(body);
	buildFullResponse(element);
}

/*Setters*/
int ResponseHandler::setMethod(HttpRequest &request)
{
	std::string methode;
	methode = request.requestLine.getMethode();
	if (methode == "GET")
		return (GET);
	else if (methode == "POST")
		return (POST);
	else if (methode == "DELETE")
		return (DELETE);
	else
		return (BAD_GATEWAY);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseHandler::buildFullResponse(HttpElement &element)
{
	std::string message;
	message += element.response->statusLine.getFullStatus();
	message += element.response->headers.getHeadersString();
	message += element.response->body.getBody();
	element.response->info.setValidResponse(true);
	element.response->info.setCompleteResponse(true);
	element.response->info.setFullResponse(message);
}
