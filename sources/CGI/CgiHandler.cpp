#include "../../includes/CGI/CgiHandler.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
CgiHandler::CgiHandler(void) : _env(), _query("NULL"), _method("NULL"),
	_name("NULL"), _fileName("NULL"), _filePath("NULL"),
	_contentDisposition("NULL"), _scriptPath("NULL"), _contentType("NULL"),
	_contentLength("NULL")
{
}

CgiHandler::~CgiHandler(void)
{
}

CgiHandler::CgiHandler(const CgiHandler &src)
{
	*this = src;
}

CgiHandler &CgiHandler::operator=(const CgiHandler &rhs)
{
	if (this != &rhs)
	{
		_env = rhs._env;
		_query = rhs._query;
		_method = rhs._method;
		_name = rhs._name;
		_fileName = rhs._fileName;
		_filePath = rhs._filePath;
		_contentDisposition = rhs._contentDisposition;
		_contentLength = rhs._contentLength;
		_scriptPath = rhs._scriptPath;
		_contentType = rhs._contentType;
	}
	return (*this);
}

void	cgiSignalHandler(int signal_num)
{
	CgiHandler	cgi;

	if (signal_num == SIGUSR1)
		cgi.closePipe();
}

/* function to execute the script */
int CgiHandler::executeScript(void)
{
	pid_t	child;

	// int		status;
	/* CHECK IF CGI SCRIPT IS NOT EMPTY --> IF EMPTY ERROR NO CONTENT? */
	if (isEmptyScriptFile())
		return (INTERNAL_SERVER_ERROR);
	/* SET ENVIRONMENT VARIABLES --> DEPENDS ON METHOD */
	setEnvironmentVar();
	/* SET UP SIGNAL HANDLER FOR CGI */
	std::signal(SIGUSR1, cgiSignalHandler);
	/* CREATE PIPE */
	if (pipe(_pfd) < 0)
		return (BAD_GATEWAY);
	/* CREATE NEW CHILD PROCESS */
	child = fork();
	if (child < 0)
		return (cgiError());
	/* ENTER THE CHILD PROCESS */
	if (child == 0)
		childProcess();
	/* ENTER THE PARENT PROCESS AND RETURN THE CORRECT STATUS CODE*/
	return (parentProcess(child));
}

int CgiHandler::parentProcess(pid_t &child)
{
	pid_t	result;
	time_t	start;
	int		status;
	int		ret;

	start = time(NULL);
	ret = OK;
	while (true)
	{
		/* WNOHANG: it tells the system not to block even
		if the child process has not yet terminated.
		This means that waitpid() will return immediately,
		instead of waiting for the child to exit. */
		result = waitpid(child, &status, WNOHANG);
		if (result == 0) // if the child process hasn't finished yet, it will return 0
		{
			// Child is still running
			if (time(NULL) - start >= 5)
			{
				std::cout << TRED << "Timeout reached. Killing child process." << TRESET << std::endl;
				kill(child, SIGKILL);
				waitpid(child, &status, 0); // Clean up
				ret = LOOP_DETECTED;
				break ;
			}
			// The parent process checks the child process frequently enough to terminate it if a timeout occurs.
			usleep(100000); // Sleep for 100 ms
		}
		else if (result > 0)
		// it returns PID Child & status if child has terminated
		{
			// Child has terminated
			if (WIFEXITED(status))
			{
				std::cout << TGREEN << "Child process exited normally." << TRESET << std::endl;
				break ;
			}
			else if (WIFSIGNALED(status))
			{
				std::cout << "Child process was killed by signal: " << WTERMSIG(status) << std::endl;
				ret = BAD_GATEWAY;
				break ;
			}
		}
		else // waitpid has failed; return == -1
		{
			std::cerr << TRED << "waitpid failed!" << TRESET << std::endl;
			ret = BAD_GATEWAY;
			break ;
		}
	}
	closePipe();
	std::cout << TGREEN << "Return in executeScript: " << ret << TRESET << std::endl;
	return (ret);
}

void CgiHandler::childProcess(void)
{
	int		fdOutfile;
	char	**envp;

	fdOutfile = open(CGIFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdOutfile < 0)
		cgiError();
	if (dup2(fdOutfile, _pfd[1]) < 0 || dup2(_pfd[1], STDOUT_FILENO) < 0)
	{
		close(fdOutfile);
		cgiError();
	}
	close(fdOutfile);
	closePipe();
	if (access((char *)_scriptPath.c_str(), X_OK) < 0)
		cgiError();
	envp = convertEnvMap();
	if (!envp)
		cgiError();
	/*
		One common reason for leftover file descriptors is that they are inherited by new processes during execve().
		To prevent this,
			you can use fcntl() to set the FD_CLOEXEC flag on the file descriptors before calling execve().
		This ensures that file descriptors are automatically closed when the child process replaces its image with a new program.
	*/
	fcntl(_pfd[0], F_SETFD, FD_CLOEXEC); // Close the read end on exec
	fcntl(_pfd[1], F_SETFD, FD_CLOEXEC); // Close the write end on exec
	char	*argv[] = {(char *)_scriptPath.c_str(), NULL};
	if (execve((char *)_scriptPath.c_str(), argv, envp) < 0)
	{
		std::cout << TRED << "Execve error" << TRESET << std::endl;
		deleteEnvpArray(envp);
		cgiError();
	}
}

/* function to close the pipe */
void CgiHandler::closePipe(void)
{
	close(_pfd[0]);
	close(_pfd[1]);
}

/* ===================== SETTERS ====================== */
void CgiHandler::setQueryString(std::string query)
{
	_query = query;
}

void CgiHandler::setMethod(std::string method)
{
	_method = method;
}

void CgiHandler::setName(std::string name)
{
	_name = name;
}

void CgiHandler::setFileName(std::string fileName)
{
	_fileName = fileName;
}

void CgiHandler::setFilePath(std::string filePath)
{
	_filePath = filePath;
}

void CgiHandler::setContentDisposition(std::string contentDisposition)
{
	_contentDisposition = contentDisposition;
}

void CgiHandler::setContentLength(std::string contentLength)
{
	_contentLength = contentLength;
}

void CgiHandler::setScriptPath(std::string scriptPath)
{
	_scriptPath = scriptPath;
}

void CgiHandler::setContentType(std::string contentType)
{
	_contentType = contentType;
}

/*Getters*/
std::string CgiHandler::getFileName(void) const
{
	return (_fileName);
}

/*PRIVATE FUNCTIONS*/

/* ====================== OTHER ======================= */
char **CgiHandler::convertEnvMap(void)
{
	int		i;
	char	**envp;

	envp = new char *[_env.size() + 1];
	if (!envp)
		return (NULL);
	i = 0;
	std::map<std::string, std::string>::const_iterator it;
	for (it = _env.begin(); it != _env.end(); ++it)
	{
		std::string env_var = it->first + "=" + it->second;
		envp[i] = strdup(env_var.c_str());
		if (!envp[i])
			return (NULL);
		++i;
	}
	envp[i] = NULL;
	return (envp);
}

void CgiHandler::deleteEnvpArray(char **envp)
{
	for (int i = 0; envp[i] != NULL; ++i)
		delete (envp[i]); // Free each allocated string
	delete[] envp;        // Free the array of pointers
}

void CgiHandler::setEnvironmentVar(void)
{
	_env["REQUEST_METHOD"] = _method;
	if (_env["REQUEST_METHOD"] == "GET")
		_env["QUERY_STRING"] = _query;
	else if (_env["REQUEST_METHOD"] == "POST")
		_env["FILE_NAME"] = _fileName;
}

int CgiHandler::cgiError(void)
{
	kill(getpid(), SIGKILL);
	closePipe();
	exit(BAD_GATEWAY);
}

bool CgiHandler::isEmptyScriptFile(void)
{
	std::string filename = ".";

	if (_method == "POST")
		filename += CGIPYSCRIPTPOST;
	else if (_method == "GET" && _scriptPath.find(CGIEXTENSION1) != std::string::npos)
		filename += CGIPYSCRIPTGET;
	else
		filename += CGIPYSCRIPTBONUS;
	std::ifstream scriptFile(filename.c_str());
	if (!scriptFile.is_open())
	{
		std::cout << TRED << "Could not open the file" << filename << TRESET << std::endl;
		return (false);
	}
	return (scriptFile.peek() == std::ifstream::traits_type::eof());
}