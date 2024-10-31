#ifndef MYSOCKET_HPP
# define MYSOCKET_HPP

# include "../Errors/SocketErrors.hpp"
# include "../Http/HttpConfig.hpp"
# include "../Project.hpp"

class Socket
{
  public:
	Socket(void);
	Socket(const Socket &ref);
	Socket &operator=(const Socket &rhs);
	~Socket(void);

	// INIT
	void init(void);
	// MEMBER

	int fd;
	int flags;
	int addrlen;
	int opt;
	int port;
	struct sockaddr_in addr;
	// EXCEPTION
	SocketErrors errors;

	// CONFIGLISTEN = INFO TO CREATE SOCKET
	ConfigListen listen;

	// FUNCTION
	Socket &get_me(void);
	int get_fd(void);
	void set_nonBlocking(void);
};

#endif
