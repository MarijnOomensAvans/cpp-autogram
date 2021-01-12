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
private:
	sqlite3* database;

	static int callback(void* data, int argc, char** argv, char** azColName);
};

