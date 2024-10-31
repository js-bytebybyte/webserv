#include "../../includes/Builder/ResponseErrorBodyBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseErrorBodyBuilder::ResponseErrorBodyBuilder(void) : errorPage(-1), errorIndex(-1), fileHandler(), body("")
{
}

ResponseErrorBodyBuilder::ResponseErrorBodyBuilder(const ResponseErrorBodyBuilder &other)
{
	*this = other;
}

ResponseErrorBodyBuilder &ResponseErrorBodyBuilder::operator=(const ResponseErrorBodyBuilder &other)
{
	if (this != &other)
	{
		errorPage = other.errorPage;
		errorIndex = other.errorIndex;
		fileHandler = other.fileHandler;
		body = other.body;
	}
	return (*this);
}

ResponseErrorBodyBuilder::~ResponseErrorBodyBuilder(void)
{
}

/*
	Function to handle the response
*/
void ResponseErrorBodyBuilder::buildErrorResponseBody(HttpElement &element, const ConfigServer &server)
{
	size_t	errors;

	errorPage = -1;
	errorIndex = -1;
	errors = server.errorsVector.size();
	for (size_t error = 0; error < errors; error++)
	{
		if (errorPage != -1 && errorIndex != -1)
			break ;
		findLocation(element, server, error);
	}
	buildError(element, server);
}

void ResponseErrorBodyBuilder::buildFallBackErrorBody(HttpElement &element)
{
	std::string errorMessage;
	errorMessage = "<!DOCTYPE html><html lang=\"en\">";
	errorMessage += "<head><meta charset=\"UTF-8\">";
	errorMessage += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">";
	errorMessage += "<title>406 Not Acceptable</title><style>body,h1,p{margin: 0;padding: 0;";
	errorMessage += "font-family: Arial,sans-serif;}body {background-color: #450505;";
	errorMessage += "color: #333;display: flex;justify-content: center;align-items: center;";
	errorMessage += "height: 100vh;}.container {text-align: center;}.error-content {";
	errorMessage += "background: rgb(24,16,16);padding: 2em 3em;border-radius: 10px;";
	errorMessage += "box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);}h1 {font-size: 3em;";
	errorMessage += "color: #ff6b6b;margin-bottom: 0.5em;}p {font-size: 1.2em;";
	errorMessage += "color: rgb(171,169,169);margin-bottom: 1.5em;}a.back-home {";
	errorMessage += "display: inline-block;padding: 0.75em 1.5em;background-color: #7f6bff;";
	errorMessage += "color: white;text-decoration: none;border-radius: 5px;font-weight: bold;";
	errorMessage += "transition: background-color 0.3s ease;}a.back-home:hover {";
	errorMessage += "background-color: #ff4b4b;}</style></head><body><div class= \"container\">";
	errorMessage += "<div class= \"error-content\"><h1>Error 406 Not Acceptable</h1><p></p>";
	errorMessage += "<a href=\"/\" class=\"back-home\">Go Back Home</a></div></div></body></html>";
	element.response->body.setBody(errorMessage);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseErrorBodyBuilder::findLocation(const HttpElement &element, const ConfigServer &server, const int &error)
{
	int	status;

	status = element.request->info.getStatus();
	for (size_t code = 0; code < server.errorsVector[error].errorCodesVector.size(); code++)
	{
		if (server.errorsVector[error].errorCodesVector[code] == status)
		{
			errorPage = error;
			errorIndex = code;
			break ;
		}
	}
}

void ResponseErrorBodyBuilder::buildError(const HttpElement &element, const ConfigServer &server)
{
	std::string errorPath;
	if (errorPage != -1 && errorIndex != -1)
		errorPath = server.errorsVector[errorPage].errorMessagePath.getPath();
	else
		errorPath = DEFAULTERROR;
	body = fileHandler.read(errorPath, false);
	element.response->body.setBody(body);
}
