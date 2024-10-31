#pragma once

#include "../../Project.hpp"
#include "ConfigFileObjectValidation.hpp"

class ConfigFileEntryValidation : public ConfigFileObjectValidation
{
  private:
	/*Private variables*/
	bool entrySymbol;
	bool entry;
	std::string entryPoint;

	/*
		Helper functions
	*/
	bool validateEntry(const std::string &entry);
	bool validateEntryValue(std::string &line);

  public:
	/* Cannonical form */
	ConfigFileEntryValidation(void);
	ConfigFileEntryValidation(const ConfigFileEntryValidation &other);
	ConfigFileEntryValidation &operator=(const ConfigFileEntryValidation &other);
	~ConfigFileEntryValidation(void);

	/*
		Function to validate the "entry" directive
	*/
	bool validate(std::istringstream &file, std::string &line);

	/*Getters*/
	bool getEntrySymbol(void) const;
	bool getEntry(void) const;
	std::string getEntryPoint(void) const;

	/*
		Function to reset the object
	*/
	void reset(void);

	/*Setters*/
	void setEntryPoint(const std::string &entryPoint);
};