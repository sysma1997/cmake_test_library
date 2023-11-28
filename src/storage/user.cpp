#include "./user.h"

#include <json/json.h>

#include "../utils/uuid.h"

namespace sysma
{
    std::string User::toString()
    {
        Json::Value json;
        json["id"] = id;
        json["name"] = name;
        json["phone"] = phone;
        json["email"] = email;
        json["password"] = password;
        json["isNull"] = isNull;

        return Json::FastWriter().write(json);
    }

    void StorageUser::init(sqlite3 *db)
    {
        this->db = db;

        std::string query{
            "CREATE TABLE IF NOT EXISTS Users("
            "id TEXT PRIMARY KEY NOT NULL, "
            "name TEXT NOT NULL, "
            "phone TEXT NOT NULL, "
            "email TEXT UNIQUE NOT NULL, "
            "password TEXT NOT NULL)"};

        char *errMsg;
        int success{sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg)};
        if (success != SQLITE_OK)
            throw std::string(errMsg) + '\n';
    }
    void StorageUser::add(User *user)
    {
        if (user->name.empty() ||
            user->phone.empty() ||
            user->email.empty() ||
            user->password.empty())
        {
            std::string message{""};

            int newLine{0};
            if (user->name.empty())
            {
                message.append("Name is required");
                newLine++;
            }
            if (user->phone.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Phone is required");
            if (user->email.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Email is required");
            if (user->password.empty())
                message.append(std::string((newLine > 0) ? "\n" : "") +
                               "Password is required");

            throw message + '\n';
        }
        if (user->password.length() != 64)
            throw std::string("Password is not sha256 or not valid\n");

        sqlite3_stmt *stmt;

        std::string query{
            "INSERT INTO Users(id, name, phone, email, password) VALUES(?, ?, ?, ?, ?)"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to insert user: " + std::string(sqlite3_errmsg(db)) + '\n';

        int pos{1};
        if (user->id.empty())
            user->id = uuid::generate_uuid_v4();
        sqlite3_bind_text(stmt, pos++, user->id.c_str(), user->id.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, user->name.c_str(), user->name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, user->phone.c_str(), user->phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, user->email.c_str(), user->email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, user->password.c_str(), user->password.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to insert user: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    void StorageUser::update(User user)
    {
        if (user.id.empty() ||
            user.name.empty() ||
            user.phone.empty() ||
            user.email.empty() ||
            user.password.empty())
        {
            std::string message{""};

            int newLine{0};
            if (user.id.empty())
            {
                message.append("Id is required");
                newLine++;
            }
            if (user.name.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Name is required");
            if (user.phone.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Phone is required");
            if (user.email.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Email is required");
            if (user.password.empty())
                message.append(std::string((newLine > 0) ? "\n" : "") +
                               "Password is required");

            throw message + '\n';
        }
        if (user.password.length() != 64)
            throw std::string("Password is not sha256 or not valid\n");

        sqlite3_stmt *stmt;

        std::string query{
            "UPDATE Users SET name = ?, phone = ?, email = ?, password = ? "
            "WHERE id = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to update user: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, user.name.c_str(), user.name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, user.phone.c_str(), user.phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, user.email.c_str(), user.email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, user.password.c_str(), user.password.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, user.id.c_str(), user.id.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to update user: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    void StorageUser::remove(std::string id)
    {
        std::string query{
            "DELETE FROM Items WHERE idUser = '" + id + "'; " +
            "DELETE FROM Users WHERE id = '" + id + "';"};

        char *errMsg;
        int success{sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg)};
        if (success != SQLITE_OK)
            throw std::string(errMsg) + '\n';
    }
    User StorageUser::get(std::string id)
    {
        if (id.empty())
            throw std::string("Id is required\n");

        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Users "
            "WHERE id = ?"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to get user: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_STATIC);

        User user;
        user.isNull = true;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            user.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            user.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            user.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            user.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            user.password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
            user.isNull = false;
        }

        sqlite3_finalize(stmt);
        return user;
    }
    User StorageUser::login(std::string email, std::string password)
    {
        if (password.length() != 64)
            throw std::string("Password is not sha256 or not valid\n");

        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Users "
            "WHERE email = ? and password = ?"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to get user: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), SQLITE_STATIC);

        User user;
        user.isNull = true;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            user.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            user.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            user.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            user.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            user.password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
            user.isNull = false;
        }

        sqlite3_finalize(stmt);
        return user;
    }
}