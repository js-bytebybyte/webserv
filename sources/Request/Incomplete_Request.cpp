#include "../../includes/Request/Incomplete_Request.hpp"

Incomplete_Request::Incomplete_Request(void) : _content_lenght(0), _header_Completed(false), _body_Completed(false), _header(""),
	_body(""), _host(""), _raw(""), _bodyCharDump()
{
	// Initialize members with default values
}
Incomplete_Request::Incomplete_Request(std::string raw_request) : _content_lenght(0), _header_Completed(false), _body_Completed(false), _header(""),
	_body(""), _host(""), _raw(""), _bodyCharDump()
{
	addHeader(raw_request);
}

Incomplete_Request &Incomplete_Request::operator=(const Incomplete_Request &req)
{
	if (this != &req)
	{
		_content_lenght = req._content_lenght;
		_header_Completed = req._header_Completed;
		_body_Completed = req._body_Completed;
		_header = req._header;
		_body = req._body;
		_host = req._host;
		_raw = req._raw;
		if (_bodyCharDump.size())
			_bodyCharDump.clear();
		_bodyCharDump = req._bodyCharDump;
	}
	return (*this);
}
Incomplete_Request::~Incomplete_Request(void)
{
}

void Incomplete_Request::addHeader(std::string content_to_add)
{
	_header += content_to_add;
	findHeaderEnd();
	if (_header_Completed == true)
	{
		getContentLength();
		if (_content_lenght != 0)
		{
			_body = _raw.substr(_header.size(),
					std::string::npos);
			_bodyCharDump.insert(_bodyCharDump.end(), content_to_add.begin()
				+ _header.size(), content_to_add.end());
		}
		if (_content_lenght == _body.size())
			_body_Completed = true;
	}
}

void Incomplete_Request::findHeaderEnd(void)
{
	unsigned long	header_end;

	header_end = _header.find("\r\n\r\n");
	if (header_end == std::string::npos)
		return ;
	_raw = _header;
	_header = _header.substr(0, header_end + 4);
	_header_Completed = true;
}

void Incomplete_Request::getContentLength(void)
{
	unsigned long	content_lenght_index;
	unsigned long	value_index;
	unsigned long	value_end;

	content_lenght_index = _header.find("Content-Length:");
	std::string content_lenght;
	if (content_lenght_index == std::string::npos)
		return ;
	value_index = _header.find_first_of(":", content_lenght_index) + 1;
	value_end = _header.find_first_of("\r\n", value_index) - 1;
	if (value_end == std::string::npos)
		return ;
	content_lenght = _header.substr(value_index, value_end - value_index + 1);
	_content_lenght = atoi(content_lenght.c_str());
}

void Incomplete_Request::addContent(std::string content_to_add)
{
	if (_header_Completed == false)
		addHeader(content_to_add);
	else
	{
		_body += content_to_add;
		/*
			JST: add content of body to the char vector
			end() is used, which means the characters will be
			inserted at the end of the vector.
		*/
		_bodyCharDump.insert(_bodyCharDump.end(), content_to_add.begin(),
			content_to_add.end());
		if (_content_lenght == _body.size())
			_body_Completed = true;
	}
}

bool Incomplete_Request::IsCompleted(void)
{
	if (_header_Completed == true && (_content_lenght == 0 || _body_Completed == true))
		return (true);
	return (false);
}
std::string Incomplete_Request::get_raw(void) const
{
	return (_raw);
}

void Incomplete_Request::set_raw(std::string str)
{
	_raw = str;
}
std::string Incomplete_Request::get_value_by_key(std::string key)
{
	size_t index = 0;
	size_t start = 0;
	size_t end = 0;
	std::string tosend = "NULL";

	if (key.empty() || _header.empty() || !_header_Completed)
		return ("NULL");

	index = _header.find(key);
	if (index != std::string::npos)
	{
		start = _header.find_first_of(":", index) + 1;
		if (start == std::string::npos)
			return ("NULL");
		end = _header.find_first_of("\r", start);

		tosend = _header.substr(start + 1, end - start);
	}

	return (tosend);
}