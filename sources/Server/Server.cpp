#include "../../includes/Server/Server.hpp"

/*PUBLIC FUNCTIONS*/

/*Canonical form*/
Server::Server() : server_fd(0), client_fd(0), flag_socket(0), client_fds(),
	bytesSentTracker(), element(), requestHandler(), responseHandler(),
	errors(), configServer(), fileHandler()
{
	_Socket = new Socket();
}

Server::Server(const Server &ref)
{
	*this = ref;
	printer("Constructor Server\n");
}

Server &Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		if (_Socket)
			delete _Socket;
		_Socket = new Socket();
		server_fd = rhs.server_fd;
		client_fd = rhs.client_fd;
		flag_socket = rhs.flag_socket;
		client_fds = rhs.client_fds;
		bytesSentTracker = rhs.bytesSentTracker;
		element = rhs.element;
		requestHandler = rhs.requestHandler;
		responseHandler = rhs.responseHandler;
		errors = rhs.errors;
		configServer = rhs.configServer;
		fileHandler = rhs.fileHandler;
	}
	return (*this);
}

Server::~Server(void)
{
	if (_Socket)
		delete _Socket;
}

/*

*/
void Server::init(void)
{
	Socket	*ms;

	ms = new Socket();
	printer("Init Server\n");
	try
	{
		/* SET NEWLY CREATED SOCKET OBJECT */
		set_Socket(ms);
		/* ASSIGN LISTEN OBJECT FROM SERVER TO SOCKET */
		_Socket->listen = configServer.listen;
		/* INIT SOCKET CREATION */
		initSocket();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Server::initSocket(void)
{
	try
	{
		_Socket->init();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	_Socket->addr.sin_addr.s_addr = INADDR_ANY;
	// Binding socket to IP
	if ((bind(_Socket->fd, (struct sockaddr *)&_Socket->addr, sizeof(_Socket->addr))) < 0)
	{
		perror("bind : ");
		close_error("BINDING");
		throw ServerErrors::BIND_ERROR();
	}
	// start listening
	if ((listen(_Socket->fd, 1000)) < 0)
	{
		close_error("LISTEN");
		throw ServerErrors::LISTEN_ERROR();
	}
	printer("Listening on port: ");
}

void Server::closing(void)
{
	if (server_fd)
		close(server_fd);
	for (size_t i = 0; i < client_fds.size(); i++)
	{
		if (client_fds.at(i))
			close(client_fds.at(i));
	}
}
void Server::close_error(const char *ref)
{
	if (server_fd)
		close(server_fd);
	for (size_t i = 0; i < client_fds.size(); i++)
	{
		if (client_fds[i])
			close(client_fds[i]);
	}
	perror(ref);
}

///////FUNCTION/////
void Server::printer(const std::string &str)
{
	if (_Socket)
	{
		std::cout << "[SERVER] fd: " << _Socket->fd << " | " << str;
		std::cout << " [ " << _Socket->listen.listenPortValue.getValue() << " ] " << std::endl;
	}
}

bool Server::Listen(int client_fd, std::string &rawRequest)
{
	std::cout << TBLUE << "~~~~ Server::Listen ~~~~ " << TRESET << std::endl;
	/* Handle the request --> only once per client */
	if (!findClientInBytesSentTracker(client_fd))
		handler(rawRequest);
	std::cout << TBLUE << "~~~~ OK write reponse ~~~~ " << TRESET << std::endl;
	if (findClientInBytesSentTracker(client_fd) && element.response == NULL)
	{
		cleanHttpRequestResponse();
		handler(rawRequest);
	}
	/* Send the request */
	return (sendResponse(client_fd));
}

void Server::handler(std::string request)
{
	long	fileSize;

	std::ifstream infile(TUNNEL, std::ios::binary);
	std::stringstream rbuffer;
	rbuffer << infile.rdbuf();
	rbuffer.seekg(0, std::ios::end);
	fileSize = rbuffer.tellg();
	if (configServer.bodySize.getValue() <= fileSize)
		handleRequest(request, false);
	else
		handleRequest(request, true);
	std::remove(TUNNEL);
}

void Server::handleRequest(std::string request, const bool &inRange)
{
	int	choice;

	if (!inRange)
		responseHandler.handleError(element, PAYLOADERROR, PAYLOAD_TOO_LARGE);
	else
	{
		if (requestHandler.handleRequest(request, element, configServer))
		{
			choice = responseHandler.setMethod(*element.request);
			responseHandler.handleResponse(choice, element, configServer);
		}
		else
			responseHandler.handleError(element, DEFAULTERROR, DEFAULTERRORPAGE);
	}
}

bool Server::findClientInBytesSentTracker(int client_fd)
{
	std::map<int, int>::iterator it;
	it = bytesSentTracker.find(client_fd);
	if (it == bytesSentTracker.end())
		return (false);
	return (true);
}

bool Server::sendResponse(int client_fd)
{
	char	sendBuffer[SMALL_BUF];
	int		bytesSent;
	int		fullResponseSize;
	bool	foundClient;

	bytesSent = 0;
	std::stringstream tmp(element.response->info.getFullResponse());
	fullResponseSize = element.response->info.getFullResponse().size();
	foundClient = findClientInBytesSentTracker(client_fd);
	/* CHECK IF CLIENT FD IS PRESENT IN BYTESTRACKER */
	if (!foundClient)
		tmp.seekg(0, std::ios::beg);
	else
		tmp.seekg(bytesSentTracker[client_fd], std::ios::beg);
	if (tmp.eof())
		return (cleanHttpRequestResponse(), false);
	// Read up to SMALL_BUF size into the buffer
	tmp.read(sendBuffer, SMALL_BUF);
	std::size_t bytesRead = tmp.gcount();
	// Send the data using the send() system call
	bytesSent = send(client_fd, sendBuffer, bytesRead, 0);
	if (bytesRead == 0 || bytesSent <= 0)
	{
		if (bytesSent < 0)
			std::cerr << TRED << "Error sending data" << TRESET << std::endl;
		bytesSentTracker.erase(client_fd);
		memset(sendBuffer, 0, SMALL_BUF);
		return (cleanHttpRequestResponse(), false); // Send failed
	}
	// Update the current position for the next call
	if (!foundClient)
		bytesSentTracker.insert(std::pair<int, int>(client_fd, bytesSent));
	else
		bytesSentTracker[client_fd] += bytesSent;
	// ADD CHECK TO SEE IF FULL RESPONSE HAS BEEN SENT AND IF CLIENT SOCKET CAN BE CLOSED
	if (bytesSentTracker[client_fd] == fullResponseSize)
	{
		std::cout << TRED << "... Closing client connection [ fd :" << client_fd << "] ... " << TRESET << std::endl;
		bytesSentTracker.erase(client_fd);
		memset(sendBuffer, 0, SMALL_BUF);
		return (cleanHttpRequestResponse(), false);
	}
	return (memset(sendBuffer, 0, SMALL_BUF), true);
}

void Server::cleanHttpRequestResponse(void)
{
	std::cout << TRED << ">>>> cleaning ... " << TRESET << std::endl;
	if (element.request)
		delete element.request;
	if (element.response)
		delete element.response;
	element.request = NULL;
	element.response = NULL;
}

/*Gettes*/
int Server::getConnection(void)
{
	int	new_client_fd;

	if ((new_client_fd = accept(_Socket->fd, (struct sockaddr *)&_Socket->addr, (socklen_t *)&_Socket->addrlen)) < 0)
	{
		close_error("ACCEPT");
		throw ServerErrors::ACCEPT_ERROR();
	}
	client_fds.push_back(new_client_fd);
	try
	{
		set_nonBlocking(client_fds.back());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (client_fds.back());
}

Socket *Server::get_Socket(void)
{
	return (_Socket);
}

/*Setters*/
void Server::set_Socket(Socket *ms)			
{
	if (!ms)
		throw ServerErrors::SOCKET_ERROR();
	if (this->_Socket)
		delete _Socket;
	_Socket = ms;
	return ;
}

void Server::set_nonBlocking(int client_fd)
{
	if ((flag_socket = fcntl(client_fd, F_GETFL, 0)) < 0)
	{
		close_error("FCNTL - GETFL : ");
		throw ServerErrors::FCNTL_ERROR();
	}
	if (fcntl(client_fd, F_SETFL, flag_socket | O_NONBLOCK) == -1)
	{
		close_error("FCNTL - FSETFL : ");
		throw ServerErrors::FCNTL_ERROR();
	}
}
