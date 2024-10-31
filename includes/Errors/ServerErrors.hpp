#pragma once

#include "../Project.hpp"

class ServerErrors
{
  public:
	/*Canonical Form*/
	ServerErrors(void);
	~ServerErrors(void);
	ServerErrors &operator=(const ServerErrors &ref);
	ServerErrors(const ServerErrors &ref);

	// EXCEPTION
	class FCNTL_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
	class SOCKET_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class FD_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class IP_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class BIND_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class LISTEN_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class ACCEPT_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class READ_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
};