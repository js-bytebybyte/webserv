#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileRouteUploadValidation : public ConfigFileObjectValidation
{
  private:
	bool uploadSymbol;
	bool upload;
	std::string uploadValue;
	std::string entry;

	/*Helper functions*/
	bool validateUploadSymbol(std::string &line);
	bool validateUpload(std::string &line);
	bool validatePath(std::string &path);

  public:
	ConfigFileRouteUploadValidation(void);
	ConfigFileRouteUploadValidation(const ConfigFileRouteUploadValidation &other);
	ConfigFileRouteUploadValidation &operator=(const ConfigFileRouteUploadValidation &other);
	~ConfigFileRouteUploadValidation(void);

	/*
		Function to validate the configuration file
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getUploadSymbol(void) const;
	bool getUpload(void) const;
	std::string getUploadValue(void) const;

	/*Helper functions*/
	void reset(void);

	/*Setters*/
	void setEntry(std::string entry);
};