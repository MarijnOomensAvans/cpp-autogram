#include <iostream>
#include <random>
#include <sqlite3.h>

static int selectData(const char* dbPath);


static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}


int main()
{
    const char* dir = "D:/GitHub/cpp-autogram/Cpp_Autogram/Data/numerals.db";
    sqlite3* DB;

    selectData(dir);

    return 0;
}

static int selectData(const char* dbPath)
{
    const char* data = "Callback function called";
    char* zErrMsg = 0;
    sqlite3* DB;

    int exit = sqlite3_open(dbPath, &DB);

    if (exit)
    {
        std::cout << "Can't open database!" << std::endl;
        return exit;
    }
    else {
        std::cout << "Succesfully opened database." << std::endl;
        std::string sql = "SELECT num FROM numerals WHERE language_id = 1 ORDER BY value;";

        int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else {
            fprintf(stdout, "Operation done successfully\n");
        }
        sqlite3_close(DB);

        return 0;
    }

}

//static int callback(void* NotUsed, int argc, char** argv, char** azColName)
//{
//    for (int i = 0; i < argc; i++)
//    {
//        std::cout << azColName[i] << ": " << argv[i] << std::endl;
//    }
//
//    std::cout << std::endl;
//
//    return 0;
//}