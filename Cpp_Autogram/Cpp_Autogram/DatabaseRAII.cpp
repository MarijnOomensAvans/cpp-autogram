#include "DatabaseRAII.h"

DatabaseRAII::DatabaseRAII(const std::string& databasePath)
{
	try
	{
		int exit = sqlite3_open(databasePath.c_str(), &database);
		if (exit)
		{
			throw std::invalid_argument("Invalid database path!");
		}

	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
	}

}

DatabaseRAII::~DatabaseRAII()
{
	sqlite3_close(database);
}

std::string DatabaseRAII::getNumeral(int number, int language)
{
	try
	{
		std::string sql = "SELECT num FROM numerals WHERE language_id = " + std::to_string(language) + " AND value = " + std::to_string(number) + ";";

		int rc = sqlite3_exec(database, sql.c_str(), callback, this, 0);

		if (rc != SQLITE_OK) {
			throw std::runtime_error("Failed to execute query: " + sql);
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
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
