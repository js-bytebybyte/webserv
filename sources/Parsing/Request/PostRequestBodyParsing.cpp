#include "../../../includes/Parsing/Request/PostRequestBodyParsing.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
PostRequestBodyParsing::PostRequestBodyParsing(void)
{
}

PostRequestBodyParsing::~PostRequestBodyParsing(void)
{
}

PostRequestBodyParsing::PostRequestBodyParsing(const PostRequestBodyParsing &other) : RequestBodyParsing(other)
{
	*this = other;
}

PostRequestBodyParsing &PostRequestBodyParsing::operator=(const PostRequestBodyParsing &other)
{
	(void)other;
	return (*this);
}

void PostRequestBodyParsing::parse(HttpRequest &request)
{
	std::istringstream stream(request.info.getFullRequest());
	std::string body;
	std::string line;
	// Skip the request line and headers
	while (std::getline(stream, line) && line != "\r")
		;
	// Store the remaining content
	std::string remainingContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	// Create a new stream with the remaining content
	std::istringstream remaining(remainingContent);
	// Select the appropriate body validator based on the request method
	requestValidator.requestBodyValidator = requestValidator.createRequestBodyValidator(request);
	if (requestValidator.requestBodyValidator)
	{
		// Parse the body
		if (requestValidator.requestBodyValidator->hasEmptyLine(line))
		{
			request.info.setEmptyLine(true);
			parseBody(remaining, request);
		}
		else
			request.info.setEmptyLine(false);
		delete requestValidator.requestBodyValidator;
		// Clean up the dynamically allocated body validator
		requestValidator.requestBodyValidator = NULL;
	}
}

/*PRIVATE FUNCTIONS*/
void PostRequestBodyParsing::unchunkBody(std::istringstream &stream, HttpRequest &request) const
{
	std::string line;
	std::string chunkData; // temp string to reconstruct the chunked body
	unsigned int chunkLen = 0;
	unsigned int chunkLenSum = 0;

	while (std::getline(stream, line))
	{
		for (size_t i = 0; i < line.length(); i++)
		{
			std::stringstream ss;
			ss << line[i];
			ss >> std::hex >> chunkLen;
			chunkLenSum += chunkLen;
			if (chunkLen == 0)
				break ;
			for (size_t j = 0; j < chunkLen; j++)
				chunkData += line[i + 1 + j];
			i += chunkLen;
		}
		break ;
	}
	if (chunkLenSum != chunkData.length())
		request.info.setStatus(BAD_REQUEST);
	else
		request.body.setBody(chunkData);
}

void PostRequestBodyParsing::parseBody(std::istringstream &stream,
	HttpRequest &request) const
{
	std::string body;
	std::string line;

	// read the body
	std::getline(stream, line);
	// if the body is empty, the request is invalid
	if (request.info.getChunked())
		unchunkBody(stream, request);
	if (requestValidator.requestBodyValidator->validate(line, request) == false)
		return ;
}