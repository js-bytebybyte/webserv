#pragma once

#include "../Project.hpp"

class Incomplete_Request
{
  public:
	unsigned long _content_lenght;
	bool _header_Completed;
	bool _body_Completed;
	std::string _header;
	std::string _body;
	std::string _host;
	std::string _raw;
	std::vector<char> _bodyCharDump;

	Incomplete_Request(void);
	Incomplete_Request(std::string raw_request);
	Incomplete_Request &operator=(const Incomplete_Request &req);
	~Incomplete_Request(void);

	void addContent(std::string content_to_add);
	bool IsCompleted(void);
	void set_raw(std::string str);
	std::string get_raw(void) const;
	std::string get_value_by_key(std::string key);

  private:
	void addHeader(std::string content_to_add);
	void findHeaderEnd(void);
	void getContentLength(void);
};
