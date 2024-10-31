#include "../../includes/Errors/SocketErrors.hpp"

/*PUBLIC FUNCTIONS*/

/*Cannonical Form*/
SocketErrors::SocketErrors(void)
{
}

SocketErrors::~SocketErrors(void)
{
}

SocketErrors::SocketErrors(const SocketErrors &ref)
{
	*this = ref;
}

SocketErrors &SocketErrors::operator=(const SocketErrors &ref)
{
	(void)ref;
	return (*this);
}

/// EXCEPTIONS
const char *SocketErrors::FCNTL_ERROR::what() const throw()
{
	return ("(Socket) FCNTL : error\n");
}

const char *SocketErrors::FD_ERROR::what() const throw()
{
	return ("(Socket) FD : error\n");
}

const char *SocketErrors::IP_ERROR::what() const throw()
{
	return ("(Socket) IP : error\n");
}

const char *SocketErrors::CONNECT_ERROR::what() const throw()
{
	return ("(Socket) CONNECT : error\n");
}

const char *SocketErrors::READ_ERROR::what() const throw()
{
	return ("(Socket) READ : error\n");
}

const char *SocketErrors::SEND_ERROR::what() const throw()
{
	return ("(Socket) SEND : error\n");
}
