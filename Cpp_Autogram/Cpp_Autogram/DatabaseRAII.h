#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>

class DatabaseRAII
{
public:
	DatabaseRAII(const std::string& databasePath);
	~DatabaseRAII();

	std::string getNumeral(int number);

	void callback(const std::string& result);
private:
	sqlite3* database;
	std::string result;

	static int callback(void* data, int argc, char** argv, char** azColName);
};

