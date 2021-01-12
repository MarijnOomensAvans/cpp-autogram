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
	const char* data = "";
	char* zErrMsg = 0;

	std::string sql = "SELECT num FROM numerals WHERE language_id = 1 AND value = " + std::to_string(number) + ";";

	int rc = sqlite3_exec(database, sql.c_str(), callback, &data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return data;
}

int DatabaseRAII::callback(void* data, int argc, char** argv, char** azColName)
{
	char** result_str = (char**)data;
	*result_str = (char*)calloc(strlen(argv[0]), sizeof(char));
	if (*result_str != 0)
	{
		strcpy(*result_str, argv[0]);
	}

	return 0;
}
