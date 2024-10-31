#include "../../../includes/Parsing/Request/RequestHeadersParsing.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
RequestHeadersParsing::RequestHeadersParsing(void)
{
}

RequestHeadersParsing::~RequestHeadersParsing(void)
{
}

RequestHeadersParsing::RequestHeadersParsing(const RequestHeadersParsing &other) : RequestParsing(other)
{
	*this = other;
}

RequestHeadersParsing &RequestHeadersParsing::operator=(const RequestHeadersParsing &other)
{
	(void)other;
	return (*this);
}

/*
  Function to pasre depending on what you will parse
  request line, headers, body, etc...
*/
void RequestHeadersParsing::parse(HttpRequest &request)
{
	std::istringstream stream(request.info.getFullRequest());
	std::string line;
	// Skip the request line
	std::getline(stream, line);
	// select the correct headers validator
	requestValidator.requestHeadersValidator = requestValidator.createRequestHeadersValidator(request);
	if (requestValidator.requestHeadersValidator)
	{
		// Parse all headers
		while (std::getline(stream, line) && line != "\r")
		{
			line = trim(line);
			if (line.empty() || requestValidator.requestHeadersValidator->getValidHeaders() == false)
				break ;
			parseSingleHeader(line, request);
		}
		if (request.headers.getSingleHeaderValueFromKey(ENCODING).compare("chunked") == 0)
		{
			requestValidator.requestHeadersValidator->chunked = true;
			request.info.setChunked(true);
		}
		// Check that the mandatory headers are there for each method
		if ((requestValidator.requestHeadersValidator->hasValidHeaders() == false) || (checkDomainNameWithHostHeader(request) == false))
		{
			request.info.setStatus(BAD_REQUEST);
			request.info.setValidRequest(false);
		}
		if (requestValidator.requestHeadersValidator->getValidHeaders() == false)
			request.headers = HttpHeaders(); // this is an empty header;
		delete requestValidator.requestHeadersValidator;
		requestValidator.requestHeadersValidator = NULL;
	}
}

/*PRIVATE FUNCTIONS*/

/*
	Function to parse a single header
	A header is defined as KEY: VALUE
	So we will look for the : to split it into a key, value pair.
	If you find one then proceed to populate the map that holds all the headers.
*/
void RequestHeadersParsing::parseSingleHeader(const std::string &line, HttpRequest &request)
{
	size_t	pos;

	if (requestValidator.requestHeadersValidator->isValidHeader(line))
	{
		pos = line.find(':');
		const std::string name = trim(line.substr(0, pos)) + ":";
		const std::string value = trim(line.substr(pos + 1));
		requestValidator.requestHeadersValidator->setSingleHeader(name, value);
		request.headers.setSingleHeader(name, value);
	}
}

bool RequestHeadersParsing::checkDomainNameWithHostHeader(HttpRequest &request)
{
	std::string hostHeaderValue;
	std::string headerHostName;
	std::vector<std::string> domains;
	bool checkDomainExists = false;

	hostHeaderValue = request.headers.getSingleHeaderValueFromKey(HOSTKEY);
	domains = request.headers.getDomainsVectorServer();
	if (!hostHeaderValue.empty())
	{
		// find the position of the : in the HOST header to locate hostName
		// f.ex: Host: localhost:4240 --> create substring headerHostName = localhost
		size_t pos = hostHeaderValue.find(":");
		if (pos != std::string::npos)
			headerHostName = hostHeaderValue.substr(0, pos);
		if (headerHostName.compare(DOMAINLESS) == 0)
			// hostname = localhost --> nothing to check!
			return (checkDomainExists = true);
		else
		{
			// loop over domainsVector from the server to check if there is
			// a match with the hostname from the request header
			for (size_t i = 0; i < domains.size(); i++)
			{
				if (domains[i].compare(headerHostName) == 0)
				{
					checkDomainExists = true;
					break ;
				}
			}
		}
	}
	return (checkDomainExists);
}