#include "./Storage.h"

#include <iostream>
#include <string>

namespace sysma
{
    sqlite3 *Storage::db;

    Storage::Storage()
    {
        int success{sqlite3_open("storage.db", &db)};
        if (success)
            throw "Can't open storage: " + std::string(sqlite3_errmsg(db)) + '\n';

        user.init(db);
    }
    Storage::~Storage() {}

}