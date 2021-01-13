#include "DatabaseRAII.h"

DatabaseRAII::DatabaseRAII(const std::string& databasePath)
{
	int exit = sqlite3_open(databasePath.c_str(), &database);

	if (exit)
	{
		std::cout << "Can't open database!" << std::endl;
	}
}

DatabaseRAII::~DatabaseRAII()
{
	sqlite3_close(database);
}

std::string DatabaseRAII::getNumeral(int number)
{
	std::string sql = "SELECT num FROM numerals WHERE language_id = 2 AND value = " + std::to_string(number) + ";";

	int rc = sqlite3_exec(database, sql.c_str(), callback, this, 0);

	if (rc != SQLITE_OK) {
		
	}

	return result;
}

void DatabaseRAII::callback(const std::string& result)
{
	this->result = result;
}

int DatabaseRAII::callback(void* data, int argc, char** argv, char** azColName)
{
	DatabaseRAII* cust = reinterpret_cast<DatabaseRAII*>(data);
	cust->callback(argv[0]);

	return 0;
}
