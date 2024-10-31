#include "../../../includes/Validation/Config/ConfigFileServerListenValidation.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ConfigFileServerListenValidation::ConfigFileServerListenValidation(void) : listenSymbol(false), listenHost(false), listenPort(false), listenIP(""),
	listenPortNumber(-1)
{
}

ConfigFileServerListenValidation::ConfigFileServerListenValidation(const ConfigFileServerListenValidation &other) : ConfigFileObjectValidation(other)
{
	*this = other;
}

ConfigFileServerListenValidation &ConfigFileServerListenValidation::operator=(const ConfigFileServerListenValidation &other)
{
	if (this != &other)
	{
		listenSymbol = other.listenSymbol;
		listenHost = other.listenHost;
		listenPort = other.listenPort;
		listenIP = other.listenIP;
		listenPortNumber = other.listenPortNumber;
	}
	return (*this);
}

ConfigFileServerListenValidation::~ConfigFileServerListenValidation(void)
{
}

/*
	Function to validate the "listen" directive, including IP address and port
*/
bool ConfigFileServerListenValidation::validate(std::istringstream &file, std::string &line)
{
	char	ipChars[16];
	int		port;

	if (!std::getline(file, line))
		return (false);
	if (!validateListen(line))
		return (false);
	// Obtain IP address and port
	if (std::sscanf(line.c_str(), LISTENPATTERN, ipChars, &port) != 2)
		return (false);
	// Validate IP address
	std::string ip(ipChars);
	if (!validateIP(ip))
		return (false);
	// Validate port
	if (!validatePort(port))
		return (false);
	listenIP = ip;
	listenPortNumber = port;
	return (true);
}

/*Getters*/
bool ConfigFileServerListenValidation::getListenSymbol(void) const
{
	return (listenSymbol);
}

bool ConfigFileServerListenValidation::getListenPort(void) const
{
	return (listenPort);
}

bool ConfigFileServerListenValidation::getListenHost(void) const
{
	return (listenHost);
}

std::string ConfigFileServerListenValidation::getListenIP(void) const
{
	return (listenIP);
}

int ConfigFileServerListenValidation::getListenPortNumber(void) const
{
	return (listenPortNumber);
}

/*
	Function to reset the object
*/
void ConfigFileServerListenValidation::reset(void)
{
	listenSymbol = false;
	listenHost = false;
	listenPort = false;
	listenIP = "";
	listenPortNumber = -1;
}

/*PRIVATE FUNCITONS*/

/*
	Helper functions to validate the "listen" directive
*/
bool ConfigFileServerListenValidation::validateListen(const std::string &line)
{
	int	size;

	size = std::strlen(LISTEN);
	if (std::strncmp(line.c_str(), LISTEN, size) != 0)
		return (false);
	listenSymbol = true;
	return (true);
}

bool ConfigFileServerListenValidation::validateIP(std::string &ip)
{
	int	octets[4];

	// Validate IP address
	if (std::sscanf(ip.c_str(), "%d.%d.%d.%d", &octets[0], &octets[1],
			&octets[2], &octets[3]) != 4)
		return (false);
	for (int i = 0; i < 4; ++i)
	{
		if (octets[i] < 0 || octets[i] > 255)
			return (false);
	}
	std::stringstream ss;
	ss << octets[0] << "." << octets[1] << "." << octets[2] << "." << octets[3];
	std::string reconstructedIP = ss.str();
	listenHost = true;
	ip = reconstructedIP;
	return (true);
}

bool ConfigFileServerListenValidation::validatePort(const int &port)
{
	// Validate port
	// lower than 1024 needs root access to bind
	// higher than 65535 is bigger than the maximum port number
	if (port < 1025 || port > 65535)
		return (false);
	listenPort = true;
	return (true);
}