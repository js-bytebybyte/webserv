#include "../../includes/Builder/ResponseRedirectionBodyBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseRedirectionBodyBuilder::ResponseRedirectionBodyBuilder(void): fileHandler()
{
}

ResponseRedirectionBodyBuilder::ResponseRedirectionBodyBuilder(const ResponseRedirectionBodyBuilder &other)
{
	*this = other;
}

ResponseRedirectionBodyBuilder &ResponseRedirectionBodyBuilder::operator=(const ResponseRedirectionBodyBuilder &other)
{
	if (this != &other)
		fileHandler = other.fileHandler;
	return (*this);
}

ResponseRedirectionBodyBuilder::~ResponseRedirectionBodyBuilder(void)
{
}

/*
	Function to handle the response body
*/
void ResponseRedirectionBodyBuilder::buildRedirectionResponseBody(HttpElement &element, const ConfigServer &server, const std::string &path, std::string &body)
{
	size_t locations;

	locations = server.locationsVector.size();
	element.request->info.setStatus(MOVED_PERMANENT);
	for (size_t i = 0; i < locations; i++)
	{
		std::string route = server.locationsVector[i].routePath.getPath();
		if (route.compare(path) == 0)
		{
			std::string file = server.locationsVector[i].indexPath.getPath();
			if (path.compare(FAVICONKEY) == 0)
				body = fileHandler.read(file, true);
			else
				body = fileHandler.read(file, false);
			return ;
		}
	}
	body = fileHandler.read(DEFAULTERROR, false);
}