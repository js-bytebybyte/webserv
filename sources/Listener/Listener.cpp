#include "../../includes/Listener/Listener.hpp"

Listener::Listener(void) : _server(), nb_serv(0), nb_client(0), max_fd(0),
	max_count(0), last_request()
{
	this->tv.tv_sec = 15;
	this->tv.tv_usec = 0;
}

Listener::Listener(const Listener &ref) : _server(), nb_serv(0), nb_client(0), max_fd(0), 
	max_count(0), last_request()
{
	(void)ref;
	this->tv.tv_sec = 5;
	this->tv.tv_usec = 0;
}

Listener &Listener::operator=(const Listener &rhs)
{
	if (this != &rhs)
		(void)rhs;
	return (*this);
}

Listener::~Listener(void)
{
	size_t	i;

	for (i = 0; i < _server.size(); i++)
		if (_server.at(i))
			delete _server.at(i);
	_server.clear();
	return ;
}

////////INIT////////

// - go through Server to set them ready to listen
// - go through Client to set them and sendign msg
// - put Server[i] to Listen mode
void Listener::init(void)
{
	std::cout << TLIGHTMAGENTA << " ============= INIT MY_LISTENER ================ \n" << TRESET;
	/* CHECK IF NB SERVERS = 0 */
	if (!httpFullConfig.serverCount.getValue())
		throw ListenerErrors::EMPTY_ARRAY_ERROR();
	/* CREATE (NEW) SERVERS */
	for (int i = 0; i < httpFullConfig.serverCount.getValue(); i++)
	{
		toFree.push_back(new Server());
		set_Server(toFree[i]);
	}
	/* INIT ALL SERVERS --> create sockets per server */
	for (int i = 0; i < httpFullConfig.serverCount.getValue(); i++)
	{
		try
		{
			_server.at(i)->init();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	try
	{
		fd_manager();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	close_all();
	std::cout << "Closing all sockets " << std::endl;
}

///////FUNCTION/////

void Listener::new_connection(Server *server)
{
	int			client_socket;
	sockaddr	addr;
	socklen_t	addr_size;

	addr_size = sizeof(sockaddr);
	if (!server)
		return ;
	client_socket = accept(server->_Socket->fd, &addr, &addr_size);
	if (client_socket < 0)
		return ;
	std::cout << "(new_connection) added  fd : " << client_socket << std::endl;
	FD_SET(client_socket, &fd_read);
}

void Listener::readRequest(int client_socket)
{
	char	buffer[SMALL_BUF];
	int		bytesReceveid;

	/*  READ SMALL_BUFF BYTES */
	bytesReceveid = recv(client_socket, buffer, SMALL_BUF, 0);
	if (bytesReceveid <= 0)
	{
		if (bytesReceveid < 0)
			std::cerr << "Error on reading request" << std::endl;
		FD_CLR(client_socket, &fd_read);
		close(client_socket);
		return ;
	}
	std::cout << "[READ REQUEST] read bytes: " << bytesReceveid << " on socket fd " << client_socket << std::endl;
	std::string raw_request(buffer, bytesReceveid);
	/* CHECK IF REQUEST IS ALREADY IN THE INCOMPLETE REQUEST MAP
		if yes --> add content
		if not --> add to incomplete request map
	*/
	if (find_incomplete(client_socket) == true)
	{
		std::cout << "FINDING INCOMPLETE REQUEST fd : " << client_socket << std::endl;
		// std::cout << _incomplete[client_socket].get_raw() << std::endl;
		_incomplete.find(client_socket)->second.addContent(raw_request);
	}
	else
	{
		std::cout << "NEW INCOMPLETE REQUEST fd : " << client_socket << std::endl;
		Incomplete_Request new_request(raw_request);
		_incomplete.insert(std::pair<int, Incomplete_Request>(client_socket, new_request));
	}
	/* CHECH IF THE REQUEST IS COMPLETE */
	if (_incomplete.find(client_socket)->second.IsCompleted() == true)
		next_Request(client_socket);
}

bool Listener::find_incomplete(int socket)
{
	std::map<int, Incomplete_Request>::iterator it;
	it = _incomplete.find(socket);
	if (it == _incomplete.end())
		return (false);
	return (true);
}

bool	createTmp(std::vector<char> &dump)
{
	std::ofstream outfile(TUNNEL);
	if (!outfile)
		return (false);
	std::string fileData;
	fileData.append((char *)dump.data(), dump.size());
	outfile << fileData;
	outfile.close();
	return (true);
}

void Listener::next_Request(int client_socket)
{
	Incomplete_Request	raw;

	if ((_incomplete.at(client_socket)._bodyCharDump.size() != 0) && !createTmp(_incomplete.at(client_socket)._bodyCharDump))
		raw.set_raw("Permission tmp.png file denied");
	else
		raw = _incomplete.find(client_socket)->second;
	completeRequest.insert(std::pair<int, Incomplete_Request>(client_socket, raw));
	_incomplete.erase(client_socket);
	FD_SET(client_socket, &fd_write);
	FD_CLR(client_socket, &fd_read);
}

int Listener::getMax_fd(const fd_set &fds)
{
	int max_fd = -1; // Start with -1 (an invalid fd) since fds start from 0
	// Iterate over all possible file descriptor values
	for (int fd = 0; fd < FD_SETSIZE; ++fd)
	{
		if (FD_ISSET(fd, &fds))
			max_fd = std::max(max_fd, fd);
	}
	std::cout << "The maximum fd in fd_set : " << max_fd << std::endl;
	return (max_fd);
}

int Listener::get_maxCount(void)
{
	if (nb_serv < nb_client)
		return (nb_client);
	else
		return (nb_serv);
}

Server *Listener::get_server_by_fd(int sockt)
{
	for (size_t i = 0; i < _server.size(); i++)
	{
		if (sockt == _server.at(i)->get_Socket()->get_fd())
		{
			std::cout << "[LISTENER] find server index / fd " << i << "/ " << sockt << std::endl;
			return (_server.at(i));
		}
	}
	return (NULL);
}
int Listener::fd_manager(void)
{
	int		activity;
	int		count;
	int		index_serv;
	Server	*_server;

	fd_set temp_read_fds, temp_write_fds;
	activity = 0;
	count = 0;
	index_serv = 0;
	// init current set of sockets
	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	// Add (master)server(s) socket to the socket sets;
	for (size_t i = 0; i < this->_server.size(); i++)
	{
		std::cout << "Server added to fd_set read and write" << std::endl;
		FD_SET(this->_server.at(i)->_Socket->fd, &fd_read);
		FD_SET(this->_server.at(i)->_Socket->fd, &fd_write);
	}
	/*  Server infinite loop for servicing the client */
	while (1)
	{
		count++;
		temp_read_fds = fd_read;
		// Copy read_fds to temporary sets for select()
		temp_write_fds = fd_write;
		// Copy write_fds to temporary sets for select()
		std::cout << TLIGHTBLUE << " SELECT WHILE LOOP " << count << TRESET << std::endl;
		// Wait for activity on any of the sockets
		activity = select(10, &temp_read_fds, &temp_write_fds, NULL, NULL);
		if (activity < 0)
		{
			perror("Select error");
			break ;
		}
		if (activity == 0)
		{
			std::cerr << "Timeout" << std::endl;
			break ;
		}
		for (int fd = 0; fd < FD_SETSIZE; fd++)
		{
			if (FD_ISSET(fd, &temp_read_fds))
			{
				_server = get_server_by_fd(fd);
				if (_server)
				{
					std::cout << TDARKGRAY << ">>New connection received on server nr " << fd;
					std::cout << " with fd: " << _server->_Socket->fd;
					std::cout << "- port [" << _server->_Socket->listen.listenPortValue.getValue();
					std::cout << "- port [" << _server->_Socket->listen.listenPortValue.getValue();
					// fd is the socket not the index of the vector _server
					std::cout << "], accept the connection." << TRESET << std::endl;
					FileHandler::displayVector(_server->configServer.domainsVector);
					/* CREATE NEW CLIENT SOCKET CONNECTION
						+ ADD IT TO FD_READ_SET */
					new_connection(_server);
					break ;
				}
				else
				{
					std::cout << "READING on fd : " << fd << std::endl;
					readRequest(fd);
					break ; // --> to go back through select()
				}
			}
			else if (FD_ISSET(fd, &temp_write_fds)) // JST --> to change be
			{
				std::cout << TBLUE << ">>Ready to write.. ? " << TRESET << std::endl;
				std::cout << TLIGHTBLUE << "SERVER Writting response on fd : " << fd << TRESET << std::endl;
				std::string raw = completeRequest[fd].get_raw();
				index_serv = postman(fd);
				if (index_serv == -1)
					index_serv = 0;
				if (!this->_server.at(index_serv)->Listen(fd, raw))
				{
					FD_CLR(fd, &fd_write);
					completeRequest.erase(fd);
					close(fd);
					break ;
				}
			}
		}
	}
	std::cout << TDARKGRAY << " end " << TRESET << std::endl;
	return (0);
}

void Listener::add_server(Server *server)
{
	if (!server)
		return ;
	if (_server.size() >= MAX_FD)
		throw ListenerErrors::INDEX_ERROR();
	_server.push_back(server);
}
void Listener::set_Server(Server *server)
{
	std::cout << "set_Server called for server with index: nb_serv: " << nb_serv << std::endl;
	if (!server)
		return ;
	if (nb_serv >= MAX_FD)
		throw ListenerErrors::INDEX_ERROR();
	/* ADD NEWLY CREATED SERVER TO THE SERVER ARRAY */
	_server.push_back(server);
	/* ASSIGN THE SERVERCONFIG TO THE NEWLY CREATED SERVER BASED ON THE INDEX */
	_server.back()->configServer = httpFullConfig.serverConfigs[nb_serv];
	nb_serv++;
	return ;
}

int Listener::postman(int fd)
{
	int	count;

	std::string _port;
	if (fd < 0)
		return (-1);
	std::vector<Server *>::iterator it;
	std::vector<Server *>::iterator end;
	count = 0;
	it = _server.begin();
	end = _server.end();
	last_request = completeRequest.find(fd)->second;
	_port = last_request.get_value_by_key("Host");
	if (_port.compare("NULL") == 0)
		return (-1);
	if ((count = get_server_by_host(_port)) > -1)
		return (count);
	return (-1);
}
void Listener::print(const std::string &str)
{
	std::cout << "[LISTENER] server : " << (nb_serv > 0 ? nb_serv : 0);
	std::cout << str;
}

bool Listener::get_port_by_server(Server *server, int port)
{
	struct sockaddr_in	addr;
	socklen_t			addr_len;

	addr_len = sizeof(addr);
	std::cout << TRED << "server port " << (server)->get_Socket()->get_fd() << std::endl;
	if (getsockname((server)->get_Socket()->get_fd(), (struct sockaddr *)&addr,
			&addr_len) == -1)
	{
		std::cout << TRED << "ERROR SOCKET" << std::endl;
		return (false);
	}
	std::cout << TRED << " nthos" << TRESET << std::endl;
	if (ntohs(addr.sin_port) == port)
	{
		std::cout << "Socket FD found for port " << port << ": " << server->get_Socket()->get_fd() << std::endl;
		return (true); // Return the matching FD
	}
	std::cout << TRED << " PorT :" << ntohs(addr.sin_port) << TRESET << std::endl;
	return (false);
}

int Listener::get_server_by_host(std::string str)
{

	int count = 0;
	int port = 0;
	size_t index ;
	std::string tmp; 
	std::string host; 
	std::string str_port = "";
	std::vector<Server *>::iterator it;
	std::vector<Server *>::iterator end;
	std::vector<std::string>::iterator it_str;
	std::vector<std::string>::iterator end_str;

	it = this->_server.begin();
	end = this->_server.end();
	index = str.find_last_of(":"); 
	if(index != std::string::npos)
	{

		host = str.substr(0,index );
		str_port = str.substr(index + 1, str.size() - index + 1 );
		if(str_port.size())
			port = FileHandler::stringToInt(str_port);
		for(; it !=end; it++)
		{

				it_str = (*it)->configServer.domainsVector.begin();
				end_str = (*it)->configServer.domainsVector.end();
		
				for(; it_str != end_str ; it_str++)
				{
					tmp  =(it_str)->c_str();
					if((tmp.compare(host) == 0) || host.compare("localhost")==0)
					{
						if(this->get_port_by_server(*it,port))
							return count;
					}
				}
				count++;
		}

		
	}

	return -1;
}
Server *Listener::get_Server(int index)
{
	if (index >= MAX_FD) // or !Server[i]
		throw ListenerErrors::INDEX_ERROR();
	return (_server.at(index));
}

void Listener::close_all(void)
{
	for (size_t i = 0; i < _server.size(); i++)
		if (_server.at(i))
			_server.at(i)->closing();
}
