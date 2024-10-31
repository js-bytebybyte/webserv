#include "../../../includes/Validation/Response/ResponseValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseValidation::ResponseValidation(void) : _macro(), _dir(), path_to_file(), last_key(), 
	last_uri(), last_method(), last_location(UNDEFINED), last_code(UNDEFINED), 
	last_cgi(false), is_file(false)
{
	_macro[CGI_PATH] = CGI_PATH;
	_macro[PYTHONPATH] = PYTHONROUTE;
	_macro[PYTHONQUERY] = PYTHONROUTE;
	_macro[PERLQUERY] = PERLROUTE;
	_macro[DELETEFILE] = TODELETE;
	_dir.push_back(DEFAULTDIR);
	_dir.push_back(CGI);
}

ResponseValidation::~ResponseValidation(void)
{
}

ResponseValidation::ResponseValidation(const ResponseValidation &other)
{
	*this = other;
}

ResponseValidation &ResponseValidation::operator=(const ResponseValidation &other)
{
	if (this != &other)
	{
		_macro = other._macro;
		_dir = other._dir;
		path_to_file = other.path_to_file;
		last_key = other.last_key;
		last_uri = other.last_uri;
		last_method = other.last_method;
		last_location = other.last_location;
		last_code = other.last_code;
		last_cgi = other.last_cgi;
		is_file = other.is_file;
	}
	return (*this);
}

bool ResponseValidation::check_in(HttpRequest &_request, std::vector<ConfigRoute> locationsVector)
{
	int	index;

	index = -1;
	last_uri = _request.requestLine.getUri();
	std::string methode = _request.requestLine.getMethode();
	check_in_bis(_request);
	is_cgi(last_uri);
	index = find_route(last_uri, locationsVector);
	if (index > -1)
	{
		if (find_methode(methode, index, locationsVector))
		{
			if (check_method(locationsVector))
				return (true);
			else
			{
				_request.info.setStatus(METHOD_NOT_ALLOWED);
				return (false);
			}
		}
		else
		{
			_request.info.setStatus(METHOD_NOT_ALLOWED);
			return (false);
		}
	}
	else
		_request.info.setStatus(BAD_GATEWAY);
	return (false);
}

bool ResponseValidation::check_out(HttpRequest &_request, std::vector<ConfigRoute> locationsVector)
{
	if (last_cgi)
	{
		if (!check_in_cgi(locationsVector))
		{
			_request.info.setStatus(METHOD_NOT_ALLOWED);
			return (false);
		}
	}
	if (is_file)
	{
		std::string path = path_to_file;
		std::string dir = locationsVector.at(last_location).uploadPath.getPath();
		std::string fullPath = dir + "/" + path;
		if (!FileHandler::is_file(fullPath) || !(access(fullPath.c_str(), R_OK) == 0) || !FileHandler::checkDirectory(dir))
		{
			_request.info.setStatus(FORBIDDEN);
			return (false);
		}
	}
	if (FileHandler::file_permission(_dir))
		return (true);
	else
	{
		_request.info.setStatus(FORBIDDEN);
		return (false);
	}
	return (true);
}

/*PRIVATE FUNCTIONS*/

/* Helper functions*/
std::string ResponseValidation::check_path(std::string uri)
{
	std::string tosend;
	tosend = FileHandler::key_path(uri, _macro);
	if (tosend != "NULL")
		tosend = _macro[tosend];
	return (tosend);
}

bool ResponseValidation::check_in_bis(HttpRequest &_request)
{
	std::string _uri = _request.requestLine.getUri();
	std::string tofind;
	path_to_file = FileHandler::get_file(_uri);
	if (path_to_file != "NULL")
		is_file = true;
	else
		is_file = false;
	tofind = check_path(_uri);
	if (tofind != "NULL")
	{
		last_uri = tofind;
		return (true);
	}
	return (false);
}

int ResponseValidation::find_route(std::string uri, std::vector<ConfigRoute> locationsVector)
{
	int	index;

	index = 0;
	std::string _uri;
	std::vector<ConfigRoute>::iterator it = locationsVector.begin();
	std::vector<ConfigRoute>::iterator end = locationsVector.end();
	for (; it != end; ++it) // Compare iterators, not the objects themselves
	{
		// Now you can access methodsVector
		std::string _uri = it->routePath.getPath();
		if (uri.compare(_uri) == 0)
		{
			last_location = index;
			return (index);
		}
		index++;
	}
	return (-1);
}

bool ResponseValidation::check_in_cgi(std::vector<ConfigRoute> locationsVector)
{
	std::string path = locationsVector.at(last_location).uploadPath.getPath();
	if (!locationsVector.at(last_location).cgi.getAuthorized())
		return (false);
	return (true);
}

bool ResponseValidation::is_cgi(std::string path)
{
	(void)path;
	if (FileHandler::map_finder(last_uri, _macro))
	{
		last_cgi = true;
		return (true);
	}
	else
		last_cgi = false;
	return (false);
}

bool ResponseValidation::find_methode(std::string _methode, int index, std::vector<ConfigRoute> locationsVector)
{
	std::vector<std::string>::iterator it = locationsVector.at(index).methodsVector.begin();
	std::vector<std::string>::iterator end = locationsVector.at(index).methodsVector.end();
	for (; it != end; ++it) // Compare iterators, not the objects themselves
	{
		// Now you can access methodsVector
		std::string methode = it->c_str();
		if (_methode == methode)
		{
			last_method = methode;
			return (true);
		}
	}
	return (false);
}

bool ResponseValidation::check_method(std::vector<ConfigRoute> locationsVector)
{
	if (last_method.empty())
		return (false);
	if (last_method.compare(DELETEKEY) == 0 || last_method.compare(POSTKEY) == 0 || last_method.compare(GETKEY) == 0)
	{
		if (FileHandler::isDirectory(locationsVector.at(last_location).uploadPath.getPath()) && FileHandler::file_permission(_dir))
			return (true);
		else
			return (false);
	}
	return (true);
}

std::string ResponseValidation::path_to_route(std::string path)
{
	size_t	index;

	std::string tosend;
	std::string tmp;
	if ((index = path.find(CGI)) != std::string::npos)
		return (path);
	if ((index = path.rfind('/')) != std::string::npos)
		tmp = path.substr(0, index + 1);
	else
		tmp = path;
	tosend = tmp;
	return (tosend);
}

int ResponseValidation::get_cgi_path(std::string tofind, std::vector<ConfigRoute> locationsVector)
{
	size_t	index;

	if (((index = tofind.find(PYTHONPATH))) != std::string::npos)
	{
		std::string macro = PYTHONPATH;
		return (true);
	}
	if ((index = tofind.find(PYTHONQUERY)) != std::string::npos)
	{
		std::string macro = PYTHONQUERY;
		last_location = find_route(PYTHONROUTE, locationsVector);
		return (true);
	}
	if ((index = tofind.find(PERLQUERY)) != std::string::npos)
	{
		std::string macro = PERLQUERY;
		last_location = find_route(PERLROUTE, locationsVector);
		return (true);
	}
	return (false);
}

template <typename T> void ResponseValidation::displayVector(const std::vector<T> &vec, std::string str)
{
	std::cout << TGREEN << " -- [ " << str << " ] --" << TRESET << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << TGREEN << "-----------" << TRESET << std::endl;
}