#include "./database.h"

#include <iostream>
#include <string>
#include <vector>

namespace sysma
{
    sqlite3 *Database::db;

    Database::Database()
    {
        char *errMessage{0};
        int success{sqlite3_open("database.db", &Database::db)};
        if (success)
        {
            std::cout << "Can't open database: " << sqlite3_errmsg(Database::db) << '\n';
            return;
        }

        std::string query{
            "CREATE TABLE IF NOT EXISTS Persons("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "name TEXT NOT NULL, "
            "phone TEXT NOT NULL, "
            "email TEXT NOT NULL)"};

        success = sqlite3_exec(Database::db, query.c_str(), NULL, 0, &errMessage);
        if (success != SQLITE_OK)
            std::cout << errMessage << '\n';
    }
    Database::~Database() {}

    void Database::addPerson(std::string name, std::string phone, std::string email, int id)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "INSERT INTO Persons(" +
            std::string((id != -1) ? "id, " : "") +
            "name, phone, email) "
            "VALUES (" +
            std::string((id != -1) ? "?, " : "") +
            "?, ?, ?)"};
        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to insert person: " << sqlite3_errmsg(Database::db) << '\n';
            return;
        }

        int pos{1};
        if (id != -1)
            sqlite3_bind_int(stmt, pos++, id);
        sqlite3_bind_text(stmt, pos++, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos, email.c_str(), email.length(), SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    Person Database::getPerson(int id)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Persons "
            "WHERE id = ?"};
        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to get person: " << sqlite3_errmsg(Database::db) << '\n';
            return Person{};
        }

        Person person;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            person.id = sqlite3_column_int(stmt, 0);

            if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
                person.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                person.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                person.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        }

        sqlite3_finalize(stmt);
        return person;
    }
    void Database::updatePerson(int id, std::string name, std::string phone, std::string email)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "UPDATE Persons SET name = ?, phone = ?, email = ? "
            "WHERE id = ?"};

        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to update person: " << sqlite3_errmsg(Database::db) << '\n';
            return;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, id);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    std::vector<Person> Database::getPersons()
    {
        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Persons "
            "WHERE id = ?"};
        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to get person: " << sqlite3_errmsg(Database::db) << '\n';
            return std::vector<Person>{};
        }

        std::vector<Person> persons;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            Person person;
            person.id = sqlite3_column_int(stmt, 0);

            if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
                person.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                person.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                person.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

            persons.push_back(person);
        }

        sqlite3_finalize(stmt);
        return persons;
    }
}