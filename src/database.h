#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

namespace sysma
{
    struct Person
    {
        int id;
        std::string name;
        std::string phone;
        std::string email;
    };

    class Database
    {
    public:
        static sqlite3 *db;

        Database();
        ~Database();

        void addPerson(std::string name, std::string phone, std::string email, int id = -1);
        Person getPerson(int id);
        void updatePerson(int id, std::string name, std::string phone, std::string email);
        void removePerson(int id);
        std::vector<Person> getPersons();
    };
}