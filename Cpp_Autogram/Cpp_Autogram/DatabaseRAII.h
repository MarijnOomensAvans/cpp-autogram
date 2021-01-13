#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>

class DatabaseRAII
{
public:
	DatabaseRAII(const std::string& databasePath);

	// Rule of 5
	~DatabaseRAII();
	DatabaseRAII(DatabaseRAII const& other) = delete;
	DatabaseRAII(DatabaseRAII&& other) = delete;
	DatabaseRAII& operator=(DatabaseRAII const& other) = delete;
	DatabaseRAII& operator=(DatabaseRAII&& other) = delete;

	std::string getNumeral(int number, int language);

	void callback(const std::string& result);
private:
	sqlite3* database;
	std::string result;

	static int callback(void* data, int argc, char** argv, char** azColName);
};

