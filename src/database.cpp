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
            "CREATE TABLE IF NOT EXISTS Users("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "name TEXT NOT NULL, "
            "phone TEXT NOT NULL, "
            "email TEXT NOT NULL, "
            "password TEXT NOT NULL)"};

        success = sqlite3_exec(Database::db, query.c_str(), NULL, 0, &errMessage);
        if (success != SQLITE_OK)
            std::cout << errMessage << '\n';
    }
    Database::~Database() {}

    void Database::addUser(std::string name, std::string phone,
                           std::string email, std::string password, int id)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "INSERT INTO Users(" +
            std::string((id != -1) ? "id, " : "") +
            "name, phone, email, password) "
            "VALUES (" +
            std::string((id != -1) ? "?, " : "") +
            "?, ?, ?, ?)"};
        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to insert User: " << sqlite3_errmsg(Database::db) << '\n';
            return;
        }

        int pos{1};
        if (id != -1)
            sqlite3_bind_int(stmt, pos++, id);
        sqlite3_bind_text(stmt, pos++, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, password.c_str(), password.length(), SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    void Database::updateUser(int id, std::string name, std::string phone,
                              std::string email, std::string password)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "UPDATE Users SET name = ?, phone = ?, email = ?, password = ? "
            "WHERE id = ?"};

        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to update User: " << sqlite3_errmsg(Database::db) << '\n';
            return;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, password.c_str(), password.length(), SQLITE_STATIC);
        sqlite3_bind_int(stmt, 5, id);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    User Database::login(std::string email, std::string password)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Users "
            "WHERE email = ? and password = ?"};
        int success{sqlite3_prepare_v2(Database::db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
        {
            std::cout << "SQLITE Error: to get User: " << sqlite3_errmsg(Database::db) << '\n';
            return User{};
        }

        User user;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            user.id = sqlite3_column_int(stmt, 0);

            if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
                user.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                user.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL)
                user.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL)
                user.password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        }

        sqlite3_finalize(stmt);
        return user;
    }
}