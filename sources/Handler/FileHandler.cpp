#include "../../includes/Handler/FileHandler.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
FileHandler::FileHandler(void)
{
}

FileHandler::FileHandler(const FileHandler &other)
{
	*this = other;
}

FileHandler &FileHandler::operator=(const FileHandler &other)
{
	(void)other;
	return (*this);
}

FileHandler::~FileHandler(void)
{
}

/*
	Function to read a file
*/
std::string FileHandler::read(const std::string &path, const bool binary) const
{
	std::string content;
	if (binary)
		content = readBinaryFile(path);
	else
		content = readFile(path);
	return (content);
}

bool FileHandler::checkDirectory(const std::string &path)
{
	DIR				*dir;
	struct dirent	*entry;

	if ((dir = opendir(path.c_str())) == NULL)
	{
		std::cout << "Cannot open file: " << path << std::endl;
		return (false);
	}
	// Read entries in the directory
	while ((entry = readdir(dir)) != NULL)
	{
		std::string entryName(entry->d_name);
		// Skip the special entries "." and ".."
		if (entryName == "." || entryName == "..")
			continue ;
		std::string fullPath = path + "/" + entryName;
		// Check if it is a directory
		if (entry->d_type == DT_DIR)
		{
			if (!checkDirectory(fullPath))
				return (false);
		}
		else
		{
			// Check file access
			if (access(fullPath.c_str(), R_OK) != 0)
			{
				std::cout << "Cannot read file: " << fullPath << std::endl;
				return (false);
			}
		}
	}
	// Close the directory
	closedir(dir);
	return (true);
}

bool FileHandler::file_permission(std::vector<std::string> _dir)
{
	for (size_t i = 0; i < _dir.size(); i++)
		if (!FileHandler::checkDirectory(_dir[i]))
			return (false);
	return (true);
}

bool FileHandler::is_file(std::string _path)
{
	struct stat	buffer;

	// Check if stat returns 0 and if the file is a regular file
	return (stat(_path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}
bool FileHandler::check_file(std::string _path, std::string root)
{
	std::string path = FileHandler::format_path(_path);
	std::string fullpath;
	std::cout << std::endl << TBLUE << " [FileHandler] is_file : path - root " << path << " - " << root << TRESET << std::endl;
	if ((fullpath = searchFileInDirectory(root, path)) != "NULL")
	{
		std::cout << std::endl << TBLUE << " [FILE_HANDLER] is_file (true) : fullpath" << fullpath << TRESET << std::endl;
		path = fullpath;
	}
	else
	{
		std::cout << std::endl << TBLUE << " [CHECK_FILE] Search inDerctory (false) : " << path << std::endl << "root : " << root << TRESET << std::endl;
		return (false);
	}
	if (FileHandler::is_file(path))
		return (true);
	else
		return (false);
}

bool FileHandler::uri_type(std::string path)
{
	size_t	index;

	// may be chane bool to str to get extension
	std::string toreturn ;
	if ((index = path.find('.')) != std::string::npos)
		return (true);
	else
		return (false);
}

std::string FileHandler::Build_root_path(std::string root, std::string path)
{
	std::string tosend = root + path;
	return (tosend);
}

std::string FileHandler::get_file(std::string path)
{
	size_t	pos;
	size_t	ln;

	ln = path.size();
	std::string path_file = "NULL";
	if ((pos = path.find(FILEPREFIX)) != std::string::npos)
	{
		path_file = path.substr(pos, ln - pos);
		ln = path.size();
		if ((pos = path_file.find('=')) != std::string::npos)
			return (path_file.substr(pos + 1, ln - pos - 1));
		else
			path_file = "NULL";
		return (path_file);
	}
	return (path_file);
}

bool FileHandler::isDirectory(const std::string &path)
{
	struct stat	pathStat;

	stat(path.c_str(), &pathStat);
	return (S_ISDIR(pathStat.st_mode)); // Check if it's a directory
}

/*PRIVATE FUNCTIONS*/

std::string FileHandler::readFile(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	return (reader(file, filename));
}

std::string FileHandler::readBinaryFile(const std::string &filename) const
{
	std::ifstream file(filename.c_str(), std::ios::binary);
	return (reader(file, filename));
}

std::string FileHandler::reader(const std::ifstream &file, const std::string &filename) const
{
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return ("");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}

std::string FileHandler::searchFileInDirectory(const std::string &directory, const std::string &fileName)
{
	DIR				*dir;
	struct dirent	*entry;

	std::string new_path;
	// Open the directory
	dir = opendir(directory.c_str());
	if (dir == NULL)
	{
		std::cerr << "Error: Unable to open directory " << directory << std::endl;
		return ("NULL");
	}
	// Iterate over the directory entries
	while ((entry = readdir(dir)) != NULL)
	{
		std::string entryName = entry->d_name;
		// Skip the special entries "." and ".."
		if (entryName == "." || entryName == "..")
			continue ;
		std::string fullPath = directory + "/" + entryName;
		// Check if the current entry is the file we are looking for
		if (entryName == fileName)
		{
			std::cout << "File '" << fileName << "' found at: " << fullPath << std::endl;
			return (closedir(dir), fullPath); // File found
		}
		// If it's a directory, recurse into it
		if (isDirectory(fullPath))
		{
			if ((new_path = searchFileInDirectory(fullPath,
						fileName)) != "NULL")
				return (closedir(dir), new_path);
			// File found in a subdirectory
		}
	}
	return (closedir(dir), "NULL");
	// File not found in this directory or its subdirectories
}

std::string FileHandler::format_path(std::string path)
{
	size_t	start;
	size_t	end;
	size_t	next;
	size_t	ln;

	start = 0;
	end = 0;
	next = 0;
	ln = path.size();
	std::string tosend;
	std::string path_file;
	start = path.find('/');
	end = path.rfind('/');
	if (path.empty() || start == std::string::npos)
		return (path);
	if (start == end || end == std::string::npos)
	{
		next = path.find('?');
		if (next == std::string::npos)
		{
			if (path == PYTHONPATH)
				return (path);
			else
				return ("NULL");
		}
		std::cout << TYELLOW << "[FORMAT_PATH] tosend(before) " << tosend << TRESET << std::endl;
		tosend = path.substr(start, next);
		std::cout << TYELLOW << "[FORMAT_PATH] tosend " << tosend << TRESET << std::endl;
		path_file = path.substr(next + 1, ln - next);
		std::cout << TYELLOW << "[FORMAT_PATH] path_file " << path_file << TRESET << std::endl;
		return (tosend);
	}
	tosend = path.substr(start, end + 1);
	return (tosend);
}

std::string FileHandler::key_path(std::string path, std::map<std::string, std::string> _macro)
{
	size_t	p_ln;
	size_t	s_ln;
	size_t	ln;

	std::string tosend = FileHandler::format_path(path);
	p_ln = path.size();
	s_ln = tosend.size();
	ln = p_ln - s_ln;
	for (std::map<std::string,
		std::string>::iterator it = _macro.begin(); it != _macro.end(); ++it)
	{
		if (tosend == it->first) // Compare with the value of the map
		{
			if (tosend == CGI_PATH)
				tosend = FileHandler::key_path(path.substr(s_ln - 1, ln + 1),
						_macro);
			return (tosend);
		}
	}
	return ("NULL");
}

bool FileHandler::map_finder(std::string path, std::map<std::string, std::string> _macro)
{
	for (std::map<std::string,
		std::string>::iterator it = _macro.begin(); it != _macro.end(); ++it)
	{
		if (path == PYTHONROUTE || path == PERLROUTE)
			// Compare with the value of the map
			return (true);
	}
	return (false);
}

int FileHandler::stringToInt(const std::string &str)
{
	int	num;

	std::string numericStr;
	// Extract numeric characters from the input string
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (std::isdigit(*it))
		{
			numericStr += *it;
		}
	}
	// If there were no numeric characters, return an error or handle as needed
	if (numericStr.empty())
	{
		std::cerr << "Conversion error: " << str << " does not contain a valid integer." << std::endl;
		return (0);
	}
	std::stringstream ss(numericStr);
	ss >> num;
	// Optional: Check if the entire string was a valid integer
	if (ss.fail() || !ss.eof())
	{
		std::cerr << "Conversion error: " << str << " is not a valid integer." << std::endl;
		return (0); // Or handle as needed
	}
	return (num);
}

void FileHandler::displayVector(std::vector<std::string> vec)
{
	std::cout << TGREEN << " -- [  DISPLAY VECOTR  ] --" << TRESET << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << TGREEN << "-----------" << TRESET << std::endl;
}