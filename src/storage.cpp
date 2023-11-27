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

        char *errMessage;
        success = sqlite3_exec(db, "PRAGMA foreign_keys = ON", NULL, 0, &errMessage);
        if (success != SQLITE_OK)
            throw std::string(errMessage) + '\n';

        user.init(db);
        item.init(db);
    }
    Storage::~Storage() {}

}