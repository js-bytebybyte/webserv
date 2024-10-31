#include "../../includes/Errors/ListenerErrors.hpp"

/*PUBLIC FUNCTIONS*/

/*Cannonical Form*/
ListenerErrors::ListenerErrors(void)
{
}

ListenerErrors::~ListenerErrors(void)
{
}

ListenerErrors::ListenerErrors(const ListenerErrors &ref)
{
	*this = ref;
}

ListenerErrors &ListenerErrors::operator=(const ListenerErrors &ref)
{
	(void)ref;
	return (*this);
}

/// EXCEPTIONS
const char *ListenerErrors::SELECT_ERROR::what() const throw()
{
	return ("(Listener) SELECT : error\n");
}
const char *ListenerErrors::EMPTY_ARRAY_ERROR::what() const throw()
{
	return ("(Listener) EMPTY ARRAY error\n");
}

const char *ListenerErrors::FD_ERROR::what() const throw()
{
	return ("(Listener) File directory error\n");
}

const char *ListenerErrors::IP_ERROR::what() const throw()
{
	return ("(Listener) IP error\n");
}

const char *ListenerErrors::CONNECT_ERROR::what() const throw()
{
	return ("(Listener) Connect error\n");
}

const char *ListenerErrors::READ_ERROR::what() const throw()
{
	return ("(Listener) Read error\n");
}

const char *ListenerErrors::SEND_ERROR::what() const throw()
{
	return ("(Listener) Send error\n");
}
const char *ListenerErrors::INDEX_ERROR::what() const throw()
{
	return ("(Listener) INDEX error\n");
}
