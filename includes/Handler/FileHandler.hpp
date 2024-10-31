#pragma once

#include "../Project.hpp"

class FileHandler
{
  private:
	/*
		Helper functions
	*/
	std::string readFile(const std::string &path) const;
	std::string readBinaryFile(const std::string &path) const;
	std::string reader(const std::ifstream &file, const std::string &filename) const;

  public:
	/*Canonical form*/
	FileHandler(void);
	FileHandler(const FileHandler &other);
	FileHandler &operator=(const FileHandler &other);
	~FileHandler(void);

	/*
		Function to read a file
	*/
	std::string read(const std::string &path, const bool binary) const;
	static int stringToInt(const std::string &str);
	static bool checkDirectory(const std::string &path);
	static bool file_permission(std::vector<std::string> _dir);
	static bool is_file(std::string path);
	static bool check_file(std::string path, std::string root);
	static bool uri_type(std::string path);
	static std::string Build_root_path(std::string root, std::string path);
	static std::string get_file(std::string path);
	static bool isDirectory(const std::string &path);
	static std::string format_path(std::string);
	static std::string searchFileInDirectory(const std::string &directory, const std::string &fileName);
	static std::string key_path(std::string path, std::map<std::string, std::string> _macro);
	static bool map_finder(std::string path, std::map<std::string, std::string> _macro);
	static void displayVector(std::vector<std::string> vec);
};
