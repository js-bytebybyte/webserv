#include "../../includes/Builder/ResponseTreeBodyBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseTreeBodyBuilder::ResponseTreeBodyBuilder(void) : fileHandler(), body(""), redirectionBodyBuilder()
{
}

ResponseTreeBodyBuilder::ResponseTreeBodyBuilder(const ResponseTreeBodyBuilder &other)
{
	*this = other;
}

ResponseTreeBodyBuilder &ResponseTreeBodyBuilder::operator=(const ResponseTreeBodyBuilder &other)
{
	if (this != &other)
	{
		fileHandler = other.fileHandler;
		body = other.body;
		redirectionBodyBuilder = other.redirectionBodyBuilder;
	}
	return (*this);
}

ResponseTreeBodyBuilder::~ResponseTreeBodyBuilder(void)
{
}

/*
	Function to handle the response body
*/
void ResponseTreeBodyBuilder::buildMethodResponseBody(HttpElement &element, const ConfigRoute &route, const ConfigServer &server, bool &found)
{
	bool	autoindex;

	std::string uri = element.request->requestLine.getUri();
	std::string redirect = route.redirectPath.getPath();
	autoindex = route.tree.getAutoindex();
	if (autoindex)
		buildListing(route);
	else if (!redirect.empty())
		redirectionBodyBuilder.buildRedirectionResponseBody(element, server, redirect, body);
	else
	{
		std::string file = route.indexPath.getPath();
		if (uri.compare(FAVICONKEY) == 0)
			body = fileHandler.read(file, true);
		else if (uri.compare(CGI_IMAGE) == 0)
			body = readImage(route);
		else if (uri.compare(TODELETE) == 0 || uri.compare(DELETEFILE) == 0)
			buildDeleteList(route);
		else
			body = fileHandler.read(file, false);
	}
	element.response->body.setBody(body);
	found = true;
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseTreeBodyBuilder::buildListing(const ConfigRoute &route)
{
	std::string path = route.rootPath.getPath();
	std::vector<std::string> list = getListing(path, false);
	body = fileHandler.read(TREEINDEXPAGE, false);
	body += createHtmlList(list);
	body += fileHandler.read(TREEINDEXEND, false);
}

std::vector<std::string> ResponseTreeBodyBuilder::getListing(const std::string &directoryPath, const bool &tree)
{
	DIR				*dir;
	struct dirent	*ent;
	struct stat		path_stat;

	std::vector<std::string> list;
	if ((dir = opendir(directoryPath.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			std::string path = directoryPath + "/" + ent->d_name;
			stat(path.c_str(), &path_stat);
			if (S_ISDIR(path_stat.st_mode))
				list.push_back(ent->d_name + std::string("/"));
			else
				list.push_back(ent->d_name);
		}
		closedir(dir);
	}
	else
		perror("");
	std::sort(list.begin(), list.end());
	if (!tree && 2 < list.size())
	{
		std::vector<std::string> options(list.begin() + 2, list.end());
		list = options;
	}
	return (list);
}

std::string ResponseTreeBodyBuilder::createHtmlList(const std::vector<std::string> &list)
{
	int	size;

	std::string html = "\n\t";
	html += TREELIST;
	html += "\n";
	for (std::vector<std::string>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		size = it->size() - 1;
		html += "\t\t";
		if ((*it)[size] == '/')
			html += TREEFOLDER + it->substr(0, size) + LISTEND + "\n";
		else
			html += TREEFILE + *it + LISTEND + "\n";
	}
	html += "\t";
	html += TREEEND;
	html += "\n";
	return (html);
}

std::string ResponseTreeBodyBuilder::readImage(const ConfigRoute &route)
{
	size_t	end;
	size_t	foundIndex;
	size_t	begin;
	size_t	final;

	std::string content;
	std::string cgiFile = fileHandler.read(CGIFILE, false);
	std::string upload = route.uploadPath.getPath();
	end = cgiFile.find(FILENAMEEND);
	foundIndex = cgiFile.find(FILENAMESTART);
	begin = foundIndex + strlen(FILENAMESTART);
	final = end - foundIndex - strlen(FILENAMESTART);
	std::string filename = cgiFile.substr(begin, final);
	std::string file = upload + "/" + filename;
	content = fileHandler.read(file, true);
	return (content);
}

bool	ResponseTreeBodyBuilder::containsWhitespace(const std::string &str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (isspace(*it))
			return (true);
	}
	return (false);
}

std::string ResponseTreeBodyBuilder::createDeleteList(const std::vector<std::string> &list)
{
	int	size;

	std::string html = "\n\t";
	for (std::vector<std::string>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		size = it->size() - 1;
		html += "\t\t";
		if ((*it)[size] == '/' || containsWhitespace(*it))
			continue ;
		else
			html += DELETEOPTION + *it + "\">" + *it + DELETEOPTIONEND + "\n";
	}
	return (html);
}

void ResponseTreeBodyBuilder::buildDeleteList(const ConfigRoute &route)
{
	std::string path = route.uploadPath.getPath();
	std::vector<std::string> list = getListing(path, false);
	body = fileHandler.read(DELETEBEGIN, false);
	body += createDeleteList(list);
	body += fileHandler.read(DELETEEND, false);
}