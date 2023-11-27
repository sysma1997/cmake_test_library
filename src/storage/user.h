#pragma once

#include <string>
#include <sqlite3.h>

namespace sysma
{
    struct User
    {
        std::string id;
        std::string name;
        std::string phone;
        std::string email;
        std::string password;

        bool isNull;
    };

    class StorageUser
    {
        sqlite3 *db;

    public:
        void init(sqlite3 *db);
        void add(User *user);
        void update(User user);
        void remove(std::string id);
        User login(std::string email, std::string password);
    };
}