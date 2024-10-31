#pragma once

#include "../../ConfigFile/ConfigServer.hpp"
#include "../../Project.hpp"
#include "../../Request/HttpRequest.hpp"

class ResponseValidation
{
  private:
	/*Helper functions*/
	std::string check_path(std::string uri);
	bool check_in_bis(HttpRequest &_request);
	int find_route(std::string _uri, std::vector<ConfigRoute> locationsVector);
	bool check_in_cgi(std::vector<ConfigRoute> locationsVector);
	bool is_cgi(std::string uri);
	bool find_methode(std::string methode, int index, std::vector<ConfigRoute> locationsVector);
	bool check_method(std::vector<ConfigRoute> locationsVector);
	std::string path_to_route(std::string path);
	int get_cgi_path(std::string tofind, std::vector<ConfigRoute> locationsVector);
	template <typename T> void displayVector(const std::vector<T> &vec, std::string str);

  public:
	/* Cannonical form*/
	ResponseValidation(void);
	~ResponseValidation(void);
	ResponseValidation(const ResponseValidation &other);
	ResponseValidation &operator=(const ResponseValidation &other);

	bool check_in(HttpRequest &request, std::vector<ConfigRoute> locationsVector);
	bool check_out(HttpRequest &request, std::vector<ConfigRoute> locationsVector);

	/*All elements*/
	std::map<std::string, std::string> _macro; // Use map for key-value pairs
	std::vector<std::string> _dir;
	std::string path_to_file;
	std::string last_key;
	std::string last_uri;
	std::string last_method;
	size_t last_location;
	int last_code;
	bool last_cgi;
	bool is_file;
};