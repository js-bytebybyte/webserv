#include "../../includes/Socket/Socket.hpp"

Socket::Socket() : fd(0), flags(0), opt(1), port(0), addr(), errors()
{
}

Socket::Socket(const Socket &ref) : fd(0), flags(0), opt(1)
{
	*this = ref;
}

Socket &Socket::operator=(const Socket &o)
{
	if (this != &o)
	{
		fd = o.fd;
		flags = o.flags;
		addrlen = o.addrlen;
		opt = o.opt;
		port = o.port;
		errors = o.errors;
		addr = o.addr;
	}
	return (*this);
}

Socket::~Socket(void)
{
}

////////INIT////////

void Socket::init(void)
{
	std::cout << "Init Socket\n";
	/* CREATE SOCKET */
	if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw SocketErrors::FD_ERROR();
	setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &this->opt, sizeof(this->opt));
	setsockopt(this->fd, SOL_SOCKET, SO_REUSEPORT, &this->opt, sizeof(this->opt));
	/* INIT STRUCT SOCKET ADDRESS */
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(this->listen.listenPortValue.getValue());
	this->addrlen = sizeof(addr);
	return ;
}

////////FUNCTION////

Socket &Socket::get_me(void)
{
	return (*this);
}

int Socket::get_fd(void)
{
	return (this->fd);
}

void Socket::set_nonBlocking(void)
{
	if ((this->flags = fcntl(this->fd, F_GETFL, 0)) < 0)
		throw SocketErrors::FCNTL_ERROR();
	if ((fcntl(this->fd, F_SETFL, this->flags | O_NONBLOCK)) < 0)
		throw SocketErrors::FCNTL_ERROR();
}
