#include "../../includes/Builder/ResponseMethodBodyBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseMethodBodyBuilder::ResponseMethodBodyBuilder(void) : treeBodyBuilder()
{
}

ResponseMethodBodyBuilder::ResponseMethodBodyBuilder(const ResponseMethodBodyBuilder &other)
{
	*this = other;
}

ResponseMethodBodyBuilder &ResponseMethodBodyBuilder::operator=(const ResponseMethodBodyBuilder &other)
{
	if (this != &other)
		treeBodyBuilder = other.treeBodyBuilder;
	return (*this);
}

ResponseMethodBodyBuilder::~ResponseMethodBodyBuilder(void)
{
}

/*
	Function to handle the response body
*/
void ResponseMethodBodyBuilder::buildMethodResponseBody(HttpElement &element, const ConfigServer &server, const int &location, bool &found,
	int &choise)
{
	if (choise == GET || choise == POST)
		buildGetResponseBody(element, server, location, found);
	else if (choise == DELETE)
		buildDeleteResponseBody(element, server, location, found);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseMethodBodyBuilder::buildGetResponseBody(HttpElement &element, const ConfigServer &server, const size_t &location, bool &found)
{
	std::string path = server.locationsVector[location].routePath.getPath();
	std::string uri = element.request->requestLine.getUri();
	if (path.compare(uri.c_str()) == 0)
		treeBodyBuilder.buildMethodResponseBody(element, server.locationsVector[location], server, found);
}

void ResponseMethodBodyBuilder::buildDeleteResponseBody(HttpElement &element, const ConfigServer &server, const size_t &location, bool &found)
{
	std::string path = server.locationsVector[location].routePath.getPath();
	if (path.compare(DELETEFILE) == 0)
		deleteFile(element, location, server);
	std::string uri = element.request->requestLine.getUri();
	if (path.compare(uri.c_str()) == 0)
		treeBodyBuilder.buildMethodResponseBody(element, server.locationsVector[location], server, found);
}

char ResponseMethodBodyBuilder::hexToChar(const std::string &hex)
{
	int	value;

	std::istringstream iss(hex);
	iss >> std::hex >> value;
	return (static_cast<char>(value));
}

std::string ResponseMethodBodyBuilder::decodeUrl(const std::string &input)
{
	std::string result;
	for (std::size_t i = 0; i < input.length(); ++i)
	{
		if (input[i] == '%' && i + 2 < input.length())
		{
			std::string hex = input.substr(i + 1, 2);
			result += hexToChar(hex);
			i += 2; // Skip over the two hex digits
		}
		else
			result += input[i];
	}
	return (result);
}

bool ResponseMethodBodyBuilder::existsFile(const std::string &filename)
{
	struct stat	buffer;

	return (stat(filename.c_str(), &buffer) == 0);
}

void ResponseMethodBodyBuilder::deleteFile(HttpElement &element,
	const size_t &location, const ConfigServer &server)
{
	std::string filename = element.request->body.getEndBody();
	std::string path = server.locationsVector[location].uploadPath.getPath();
	std::string file = path + "/" + decodeUrl(filename);
	if (existsFile(file))
		std::remove(file.c_str());
	else
	{
		element.response->statusLine.setStatusCode(NOTFOUND);
		element.request->requestLine.setUri("/unknowndir");
	}
}