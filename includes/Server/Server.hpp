#pragma once

#include "../ConfigFile/ConfigRoute.hpp"
#include "../ConfigFile/ConfigServer.hpp"
#include "../Errors/ServerErrors.hpp"
#include "../Handler/FileHandler.hpp"
#include "../Handler/RequestHandler.hpp"
#include "../Handler/ResponseHandler.hpp"
#include "../Http/HttpElement.hpp"
#include "../Project.hpp"
#include "../Socket/Socket.hpp"

class Server
{
  private:
	void handler(std::string request);
	bool sendResponse(int client_fd);

  public:
	/* Cannonical form*/
	Server(void);
	Server(const Server &ref);
	Server &operator=(const Server &rhs);
	~Server(void);

	/*
		Setup
	*/
	void init(void);
	void initSocket(void);
	void closing(void);
	void close_error(const char *ref);

	// FUNCTION
	void printer(const std::string &str);
	bool Listen(int client_fd, std::string &rawRequest);
	void handleRequest(std::string request, const bool &flag);

	/*Gettes*/
	int getConnection(void);
	Socket *get_Socket(void);

	/*Setters*/
	void set_Socket(Socket *ms);
	void set_nonBlocking(int new_socket);

	// MEMBER
	/*NEED TO BE PRIVATE OR CLEANUP IN OTHER OBJECTS*/
	Socket *_Socket;
	int server_fd;
	int client_fd;
	int flag_socket;
	std::vector<int> client_fds;
	std::map<int, int> bytesSentTracker;

	bool findClientInBytesSentTracker(int client_fd);
	void cleanHttpRequestResponse(void);

	HttpElement element;
	RequestHandler requestHandler;
	ResponseHandler responseHandler;
	ServerErrors errors;
	ConfigServer configServer;
	FileHandler fileHandler;
};
