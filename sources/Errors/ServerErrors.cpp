#include "../../includes/Errors/ServerErrors.hpp"

/*PUBLIC FUNCTIONS*/

/*Cannonical Form*/
ServerErrors::ServerErrors(void)
{
}

ServerErrors::~ServerErrors(void)
{
}

ServerErrors::ServerErrors(const ServerErrors &ref)
{
	*this = ref;
}

ServerErrors &ServerErrors::operator=(const ServerErrors &ref)
{
	(void)ref;
	return (*this);
}

/// EXCEPTIONS
const char *ServerErrors::FCNTL_ERROR::what() const throw()
{
	return ("(Server) FCNTL : error\n");
}

const char *ServerErrors::SOCKET_ERROR::what() const throw()
{
	return ("(Server) SOCKET : error\n");
}

const char *ServerErrors::FD_ERROR::what() const throw()
{
	return ("(Server) FD : error\n");
}

const char *ServerErrors::IP_ERROR::what() const throw()
{
	return ("(Server) IP : error\n");
}

const char *ServerErrors::BIND_ERROR::what() const throw()
{
	return ("(Server) BIND : error\n");
}

const char *ServerErrors::LISTEN_ERROR::what() const throw()
{
	return ("(Server) LISTEN : error\n");
}

const char *ServerErrors::ACCEPT_ERROR::what() const throw()
{
	return ("(Server) ACCEPT : error\n");
}

const char *ServerErrors::READ_ERROR::what() const throw()
{
	return ("(Server) READ : error\n");
}
