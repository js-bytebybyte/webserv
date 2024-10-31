#include "../../includes/Builder/ResponseBodyBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseBodyBuilder::ResponseBodyBuilder(void) : body(""), found(false), fileHandler(), methodBodyBuilder(),
	errorBodyBuilder()
{
}

ResponseBodyBuilder::ResponseBodyBuilder(const ResponseBodyBuilder &other)
{
	*this = other;
}

ResponseBodyBuilder &ResponseBodyBuilder::operator=(const ResponseBodyBuilder &other)
{
	if (this != &other)
	{
		body = other.body;
		found = other.found;
		fileHandler = other.fileHandler;
		methodBodyBuilder = other.methodBodyBuilder;
		errorBodyBuilder = other.errorBodyBuilder;
	}
	return (*this);
}

ResponseBodyBuilder::~ResponseBodyBuilder(void)
{
}

/*
	Function to handle the response
*/
void ResponseBodyBuilder::buildResponseBody(HttpElement &element, const ConfigServer &server, int &choise, ResponseValidation &responseValidation)
{
	bool	cgiFlag;
	size_t	locations;

	cgiFlag = false;
	locations = server.locationsVector.size();
	std::string uri = element.request->requestLine.getUri();
	std::string filePath;
	if (choise == POST)
		preparePostBody(element, filePath, server, responseValidation);
	if (uri.find(DELETEFILE) != std::string::npos)
		prepareDeleteBody(element, choise, uri);
	checkForCgi(element, server, choise, cgiFlag, uri, filePath);
	if (!cgiFlag)
	{
		for (size_t location = 0; location < locations; location++)
		{
			if (found)
				break ;
			methodBodyBuilder.buildMethodResponseBody(element, server, location, found, choise);
		}
		if (!found)
			buildErrorResponseBody(element, server, false);
	}
	contentLength(element);
	found = false;
}

void ResponseBodyBuilder::buildErrorResponseBody(HttpElement &element, const ConfigServer &server, const bool &fallback)
{
	if (fallback)
		errorBodyBuilder.buildFallBackErrorBody(element);
	else
		errorBodyBuilder.buildErrorResponseBody(element, server);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseBodyBuilder::contentLength(const HttpElement &element)
{
	size_t	contentLength;

	contentLength = element.response->body.getBody().size();
	std::stringstream ss;
	ss << contentLength << "\r\n";
	element.response->headers.setSingleHeader(CONTENTLENGTHKEY, ss.str());
}

void ResponseBodyBuilder::buildCgiResponseBody(HttpElement &element,
	const ConfigServer &server)
{
	if (element.request->info.getStatus() != OK)
		buildErrorResponseBody(element, server, false);
	else
		element.response->body.setBody(fileHandler.read(CGIFILE, false));
}

bool ResponseBodyBuilder::isCgi(const int &choise, const std::string &uri)
{
	if (choise == GET && uri.find(CGIPYSCRIPTGET) != std::string::npos)
		return (true);
	else if (choise == POST && uri.find(CGIPYSCRIPTPOST) != std::string::npos)
		return (true);
	else if (choise == GET && uri.find(CGIPYSCRIPTBONUS) != std::string::npos)
		return (true);
	else
		return (false);
}

void ResponseBodyBuilder::checkForCgi(HttpElement &element, const ConfigServer &server, const int &choise, bool &cgiFlag,
	const std::string &uri, const std::string &filePath)
{
	std::size_t foundCGI = uri.find(CGI_PATH);
	if (!filePath.empty())
		element.request->cgiHandler.setFilePath(filePath);
	if (foundCGI != std::string::npos)
	{
		if (isCgi(choise, uri))
		{
			std::string p = ".";
			if (choise == GET)
			{
				std::size_t foundQ = uri.find(SCRIPTSEPARATOR);
				if (foundQ != std::string::npos)
					element.request->cgiHandler.setQueryString(uri.substr(foundQ + 1));
				if (uri.find(CGIEXTENSION1) != std::string::npos)
					element.request->cgiHandler.setScriptPath(p + CGIPYSCRIPTGET);
				else
					element.request->cgiHandler.setScriptPath(p + CGIPYSCRIPTBONUS);
			}
			else
				element.request->cgiHandler.setScriptPath(p + CGIPYSCRIPTPOST);
			element.request->cgiHandler.setMethod(element.request->requestLine.getMethode());
			element.request->info.setStatus(element.request->cgiHandler.executeScript());
			cgiFlag = true;
		}
		buildCgiResponseBody(element, server);
	}
}

std::string ResponseBodyBuilder::trim(const std::string &str) const
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");
	std::string trimmed;

	if (start == std::string::npos)
		trimmed = "";
	else
		trimmed = str.substr(start, end - start + 1);
	return (trimmed);
}

void ResponseBodyBuilder::transcribeBody(const std::string &filePath, const std::string &endBody)
{
	int	empty;

	std::ifstream infile(TUNNEL, std::ios::binary);
	std::stringstream rbuffer;
	std::string lines;
	rbuffer << infile.rdbuf();
	empty = 0;
	while (1)
	{
		std::getline(rbuffer, lines);
		lines = trim(lines);
		// skip the empty line separating the body from delimiter
		if (lines.compare("") == 0)
			empty++;
		if (empty == 1)
			break ;
	}
	std::ofstream final(filePath.c_str());
	std::string endlines;
	while (1)
	{
		std::getline(rbuffer, lines);
		endlines = trim(trim(lines));
		if (endlines.compare(endBody) == 0)
			break ;
		final.write(lines.c_str(), lines.size());
		final << '\n';
	}
}

void ResponseBodyBuilder::preparePostBody(HttpElement &element, std::string &filePath, const ConfigServer &server, ResponseValidation &responseValidation)
{
	size_t	index;

	index = responseValidation.last_location;
	std::string uploadPath = server.locationsVector[index].uploadPath.getPath() + "/";
	std::string filename = element.request->cgiHandler.getFileName();
	std::string endBody = element.request->body.getEndBody();
	if(filename.compare("NULL") != 0)
	{
		filePath = uploadPath + filename.substr(strlen(FILEPREFIX));
		transcribeBody(filePath, endBody);
	}
}

void ResponseBodyBuilder::prepareDeleteBody(HttpElement &element, int &choise, const std::string &uri)
{
	size_t	found;
	size_t	filePosition;

	std::string prefix = "?";
	prefix += FILEPREFIX;
	std::string method = "DELETE";
	std::string http = "HTTP/1.1";
	element.request->requestLine.setMethode(method);
	element.request->requestLine.setHttp(http);
	found = uri.find(prefix);
	filePosition = found + prefix.size();
	std::string filename = uri.substr(filePosition);
	element.request->body.setEndBody(filename);
	element.request->requestLine.setUri(DELETEFILE);
	std::string newUri = element.request->requestLine.getUri();
	std::string requestLine = method + " " + newUri + " " + http;
	element.request->requestLine.setFullRequestLine(requestLine);
	choise = DELETE;
}
