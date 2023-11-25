#include "./user.h"

#include "../uuid.h"

namespace sysma
{
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

        char *errMessage;
        int success{sqlite3_exec(db, query.c_str(), NULL, 0, &errMessage)};
        if (success != SQLITE_OK)
            throw std::string(errMessage) + '\n';
    }
    void StorageUser::add(std::string name, std::string phone,
                          std::string email, std::string password)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "INSERT INTO Users(id, name, phone, email, password) VALUES(?, ?, ?, ?, ?)"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to insert user: " + std::string(sqlite3_errmsg(db)) + '\n';

        int pos{1};
        std::string id{uuid::generate_uuid_v4()};
        sqlite3_bind_text(stmt, pos++, id.c_str(), id.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, password.c_str(), password.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to insert user: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    void StorageUser::update(std::string id, std::string name, std::string phone,
                             std::string email, std::string password)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "UPDATE Users SET name = ?, phone = ?, email = ?, password = ? "
            "WHERE id = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to update user: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, phone.c_str(), phone.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, password.c_str(), password.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, id.c_str(), id.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_OK)
            throw "SQLITE Error: to update user: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    void StorageUser::remove(std::string id)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "DELETE FROM Users WHERE id = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to remove user: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_OK)
            throw "SQLITE Error: to remove user: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    User StorageUser::login(std::string email, std::string password)
    {
        sqlite3_stmt *stmt;

        std::string query{
            "SELECT * FROM Users "
            "WHERE email = ? and password = ?"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to get User: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, email.c_str(), email.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), SQLITE_STATIC);

        User user;
        user.isNull = true;
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            user.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));

            if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
                user.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                user.phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL)
                user.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            if (sqlite3_column_type(stmt, 4) != SQLITE_NULL)
                user.password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
            user.isNull = false;
        }

        sqlite3_finalize(stmt);
        return user;
    }
}