#pragma once

#include "../Errors/ListenerErrors.hpp"
#include "../Project.hpp"
#include "../Request/Incomplete_Request.hpp"
#include "../Server/Server.hpp"

class	Server;
class	Client;
class Listener
{
  private:
	std::vector<Server *> toFree;

  public:
	Listener(void);
	Listener(const Listener &ref);
	Listener &operator=(const Listener &rhs);
	~Listener(void);

	// MEMBER
	struct timeval tv;
	// Let use a vector to store ther server , is more ez to handle
	std::vector<Server *> _server;
	fd_set set;
	int nb_serv; // index of the _Server array
	int nb_client;
	int max_fd;
	int max_count;

	/* NEW */
	Incomplete_Request last_request;
	fd_set fd_read;
	fd_set fd_write;
	std::map<int, Incomplete_Request> _incomplete;
	std::map<int, Incomplete_Request> completeRequest;
	std::map<int, std::vector<char> > completeRequestTemp;

	// INIT
	void init(void);

	// FUNCTION
	int getMax_fd(const fd_set &fds);
	int get_maxCount(void);
	void print(const std::string &str);
	int fd_manager(void);
	int get_server_by_host(std::string host);
	Server *get_server_by_fd(int sockt);
	void set_Server(Server *server);
	Server *get_Server(int index);
	void close_all(void);
	int postman(int fd); // get server by fd

	/* NEW FUNCTIONS */
	bool get_port_by_server(Server * server,int port);
	int get_socket_by_fd();
	Incomplete_Request get_Incomplet_request(int fd);
	void add_server(Server *server);
	void readRequest(int client_socket);
	void new_connection(Server *server);
	bool find_incomplete(int socket);
	void next_Request(int client_socket);

	// EXCEPTION
	ListenerErrors errors;
	HttpConfig httpFullConfig;
};
