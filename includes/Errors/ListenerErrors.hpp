#pragma once

#include "../Project.hpp"

class ListenerErrors
{
  public:
	/*Cannonical Form*/
	ListenerErrors(void);
	~ListenerErrors(void);
	ListenerErrors(const ListenerErrors &ref);
	ListenerErrors &operator=(const ListenerErrors &ref);

	class SELECT_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
	class EMPTY_ARRAY_ERROR : public std::exception
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
	class INDEX_ERROR : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};
};