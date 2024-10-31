#pragma once

#include "../Project.hpp"
#include "ConfigCgi.hpp"
#include "ConfigPath.hpp"
#include "ConfigTree.hpp"

class ConfigRoute
{
  public:
	/* Cannonical form*/
	ConfigRoute(void);
	ConfigRoute(const ConfigRoute &other);
	ConfigRoute &operator=(const ConfigRoute &other);
	~ConfigRoute(void);

	/*
		objects holding the information
	*/
	ConfigPath routePath;
	std::vector<std::string> methodsVector;
	ConfigPath rootPath;
	ConfigPath indexPath;
	ConfigTree tree;
	ConfigPath redirectPath;
	ConfigPath uploadPath;
	ConfigCgi cgi;
};
