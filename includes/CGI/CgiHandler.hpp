#pragma once

#include "../Project.hpp"

class CgiHandler
{
  private:
	/* Private variables */
	int _pfd[2];
	std::map<std::string, std::string> _env;
	std::string _query;              // URI when GET REQUEST
	std::string _method;             // SOURCE = REQUESTLINE URI
	std::string _name;               // POST
	std::string _fileName;           // POST
	std::string _filePath;           // POST
	std::string _contentDisposition; // POST
	std::string _scriptPath;         // URI
	std::string _contentType;        // POST
	std::string _contentLength;      // headers

	/*Helper functions*/
	char **convertEnvMap(void);
	void deleteEnvpArray(char **envp);
	void setEnvironmentVar(void);
	int cgiError(void);
	bool isEmptyScriptFile(void);

  public:
	/* Cannonical form*/
	CgiHandler(void);
	~CgiHandler(void);
	CgiHandler(const CgiHandler &src);
	CgiHandler &operator=(const CgiHandler &rhs);

	/* setters */
	void setQueryString(std::string query);
	void setMethod(std::string method);
	void setName(std::string name);
	void setFileName(std::string fileName);
	void setFilePath(std::string filePath);
	void setContentDisposition(std::string contentDisposition);
	void setContentLength(std::string contentLength);
	void setScriptPath(std::string scriptName);
	void setContentType(std::string contentType);

	/*Getters*/
	std::string getFileName(void) const;

	/* function to execute the script */
	int executeScript(void);
	/* function to close pipe */
	void closePipe(void);
	/* function for the child process */
	void childProcess(void);
	/* function for the child process */
	int parentProcess(pid_t &child);
};
