#include "../../includes/Http/HttpConfig.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
HttpConfig::HttpConfig(void) : fileContent("NULL"), filePath(), serverCount(), serverConfigs()
{
}

HttpConfig::HttpConfig(ConfigPath fileName) : fileContent("NULL"), filePath(fileName), serverCount(), serverConfigs()
{
}

HttpConfig::HttpConfig(const HttpConfig &other)
{
	*this = other;
}

HttpConfig &HttpConfig::operator=(const HttpConfig &other)
{
	if (this != &other)
	{
		fileContent.str(other.fileContent.str());
		filePath = other.filePath;
		serverCount = other.serverCount;
		serverConfigs = other.serverConfigs;
	}
	return (*this);
}

HttpConfig::~HttpConfig(void)
{
}

/*Getters*/
const std::istringstream &HttpConfig::getFileContent(void) const
{
	return (fileContent);
}

/*Setters*/
void HttpConfig::setFileContent(std::istringstream &content)
{
	fileContent.str(content.str());
	fileContent.clear();
}

/*
	Print the configuration
*/
void HttpConfig::printConfig(void) const
{
	std::cout << "File content: " << fileContent.str() << std::endl;
	std::cout << "File path: " << filePath.getPath() << std::endl;
	std::cout << "Server amount: " << serverCount.getValue() << std::endl;
	for (size_t i = 0; i < serverConfigs.size(); i++)
	{
		std::cout << "Server " << i << std::endl;
		serverConfigs[i].printConfig();
	}
	std::cout << "-----------------------------------" << std::endl;
}