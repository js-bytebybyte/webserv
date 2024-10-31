#pragma once

#include "../Project.hpp"

class SocketErrors
{
  public:
	/*Cannonical Form*/
	SocketErrors(void);
	~SocketErrors(void);
	SocketErrors(const SocketErrors &ref);
	SocketErrors &operator=(const SocketErrors &ref);

	// EXCEPTION
	class FCNTL_ERROR : public std::exception
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
	class CONNECT_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
	class READ_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
	class SEND_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
};
