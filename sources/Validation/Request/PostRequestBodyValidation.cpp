#include "../../../includes/Validation/Request/PostRequestBodyValidation.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
PostRequestBodyValidation::PostRequestBodyValidation(void)
{
}

PostRequestBodyValidation::~PostRequestBodyValidation(void)
{
}

PostRequestBodyValidation::PostRequestBodyValidation(const PostRequestBodyValidation &other) : RequestBodyValidation(other)
{
	*this = other;
}

PostRequestBodyValidation &PostRequestBodyValidation::operator=(const PostRequestBodyValidation &other)
{
	(void)other;
	return (*this);
}

bool PostRequestBodyValidation::validate(std::string &bodyLine, HttpRequest &request)
{
	size_t	bodyLinePos;
	size_t	beginContent;
	int		length;

	// Check if the body is empty return if it is
	if (hasBody(bodyLine, request) == false)
		return (false);
	// Extract the boundary value
	std::string boundary = request.headers.getSingleHeaderValueFromKey(CONTENTTYPEKEY);
	std::string delimiter = getDelimiter(boundary);
	if (isLimiterSame(bodyLine, request) == false)
		return (false);
	// get only the body content
	std::string stream(request.info.getFullRequest());
	bodyLinePos = stream.find(bodyLine); // boundary
	std::string remainingContent = stream.substr(bodyLinePos + bodyLine.size());
	std::string contentType = "Content-Type: image/png\r\n";
	beginContent = remainingContent.find(contentType);
	length = contentType.size();
	std::string fileContent = remainingContent.substr(beginContent + length);
	parseMultipartBody(remainingContent, bodyLine, request);
	if (validateRest(remainingContent, bodyLine, request) == false)
		return (false);
	return (true);
}

bool PostRequestBodyValidation::validateRest(std::string &content,
	std::string &bodyLine, HttpRequest &request)
{
	std::istringstream stream(content);
	std::string line;
	std::string end = trim(trim(bodyLine)) + "--\r";
	std::string body;
	body += bodyLine + "\r\n";
	while (std::getline(stream, line))
		body += line + "\r\n";
	// Check if the body is complete
	if (trim(getLine(body)) == trim(end))
	{
		request.info.setValidRequest(true);
		request.info.setCompleteRequest(true);
		request.body.setBody(trim(body));
		return (true);
	}
	request.info.setValidRequest(false);
	request.info.setCompleteRequest(true);
	return (false);
}

/*PRIVATE FUNCTIONS*/
std::string PostRequestBodyValidation::getLine(const std::string &content)
{
	std::istringstream stream(content);
	std::string line;
	std::string currentLine;
	while (std::getline(stream, currentLine))
		line = currentLine;
	return (line);
}

bool PostRequestBodyValidation::hasBody(std::string &bodyLine, HttpRequest &request)
{
	if (bodyLine.size() <= 0)
	{
		request.info.setValidRequest(false);
		request.info.setCompleteRequest(true);
		return (false);
	}
	return (true);
}

bool PostRequestBodyValidation::isLimiterSame(std::string &bodyLine, HttpRequest &request)
{
	std::string boundary = request.headers.getSingleHeaderValueFromKey(CONTENTTYPEKEY);
	std::string delimiter = getDelimiter(boundary);
	if (bodyLine.find(delimiter) == std::string::npos)
	{
		request.info.setValidRequest(false);
		request.info.setCompleteRequest(true);
		return (false);
	}
	return (true);
}

std::string PostRequestBodyValidation::getDelimiter(std::string &boundary)
{
	std::string delimiter;
	std::size_t boundaryPos = boundary.find(LIMIT);
	if (boundaryPos != std::string::npos)
		delimiter = boundary.substr(boundaryPos + strlen(LIMIT));
	else
		delimiter = "NULL";
	return (delimiter);
}

std::string PostRequestBodyValidation::removeQuote(const std::string &str)
{
	size_t	start;
	size_t	end;

	start = str.find_first_not_of("\"");
	end = str.find("\"", start);
	std::string trimmed;
	if (start == std::string::npos)
		trimmed = "";
	else
		trimmed = str.substr(start, end - start);
	return (trimmed);
}

void PostRequestBodyValidation::collectCgiInfo(const std::string &content, HttpRequest &request)
{
	std::istringstream stream(content);
	std::string contentDisposition;
	std::string line;
	std::string name;
	std::string fileName;
	while (std::getline(stream, line))
	{// need to check it out
		if (std::getline(stream, contentDisposition, ';'))
			request.cgiHandler.setContentDisposition(contentDisposition);
		if (std::getline(stream, name, ';'))
			request.cgiHandler.setName(trim(name));
		if (std::getline(stream, fileName, '\n'))
		{
			// ex: filename="r.gif"
			std::size_t found = fileName.find('=');
			if (found != std::string::npos)
			{
				fileName = removeQuote(fileName.substr(found + 1));
				request.cgiHandler.setFileName("filename=" + fileName);
			}
		}
		// Content-Type: image/gif
		std::getline(stream, line);// need to check it out
		{
			std::size_t pos = line.find(':');
			if (pos != std::string::npos)
				request.cgiHandler.setContentType(trim(line.substr(pos + 1)));
		}
		break ;
	}
}

void PostRequestBodyValidation::parseMultipartBody(std::string &content, std::string &bodyLine, HttpRequest &request)
{
	std::string endBody = trim(trim(bodyLine)) + "--";
	request.body.setEndBody(endBody);
	collectCgiInfo(content, request);
}
