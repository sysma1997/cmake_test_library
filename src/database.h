#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

namespace sysma
{
    struct User
    {
        int id;
        std::string name;
        std::string phone;
        std::string email;
        std::string password;
    };

    class Database
    {
    public:
        static sqlite3 *db;

        Database();
        ~Database();

        void addUser(std::string name, std::string phone,
                     std::string email, std::string password, int id = -1);
        void updateUser(int id, std::string name, std::string phone,
                        std::string email, std::string password);
        void removeUser(int id);
        User login(std::string email, std::string password);
    };
}