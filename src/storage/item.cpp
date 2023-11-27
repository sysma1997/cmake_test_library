#include "./item.h"

#include <optional>

#include "../utils/uuid.h"

namespace sysma
{
    void StorageItem::init(sqlite3 *db)
    {
        this->db = db;

        std::string query{
            "CREATE TABLE IF NOT EXISTS Items("
            "id TEXT PRIMARY KEY NOT NULL, "
            "idUser TEXT NOT NULL, "
            "ref TEXT NOT NULL, "
            "name TEXT NOT NULL, "
            "price REAL NOT NULL, "
            "quantity INTEGER NOT NULL,"
            "FOREIGN KEY(idUser) REFERENCES Users(id))"};

        char *errMsg;
        int success{sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg)};
        if (success != SQLITE_OK)
            throw std::string(errMsg) + '\n';
    }
    void StorageItem::add(Item *item)
    {
        std::optional<double> price{item->price};
        std::optional<int> quantity{item->quantity};
        if (item->idUser.empty() ||
            item->ref.empty() ||
            item->name.empty() ||
            !price ||
            !quantity)
        {
            std::string message{""};

            int newLine{0};
            if (item->idUser.empty())
            {
                message.append("idUser is required");
                newLine++;
            }
            if (item->ref.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Reference is required");
            if (item->name.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Name is required");
            if (!price)
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Price is required");
            if (!quantity)
                message.append(std::string((newLine > 0) ? "\n" : "") +
                               "Quantity is required");

            throw message + '\n';
        }

        sqlite3_stmt *stmt;
        std::string query{
            "INSERT INTO Items(id, idUser, ref, name, price, quantity) "
            "VALUES(?, ?, ?, ?, ?, ?)"};
        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to insert item: " + std::string(sqlite3_errmsg(db)) + '\n';

        int pos{1};
        if (item->id.empty())
            item->id = uuid::generate_uuid_v4();
        sqlite3_bind_text(stmt, pos++, item->id.c_str(), item->id.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, item->idUser.c_str(), item->idUser.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, item->ref.c_str(), item->ref.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, pos++, item->name.c_str(), item->name.length(), SQLITE_STATIC);
        sqlite3_bind_double(stmt, pos++, item->price);
        sqlite3_bind_int(stmt, pos++, item->quantity);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to insert item: " + std::string(sqlite3_errmsg(db)) + '\n';
        sqlite3_finalize(stmt);
    }
    void StorageItem::update(Item item)
    {
        std::optional<double> price{item.price};
        std::optional<int> quantity{item.quantity};
        if (item.id.empty() ||
            item.ref.empty() ||
            item.name.empty() ||
            !price ||
            !quantity)
        {
            std::string message{""};

            int newLine{0};
            if (item.id.empty())
            {
                message.append("Id is required");
                newLine++;
            }
            if (item.ref.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Reference is required");
            if (item.name.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Name is required");
            if (!price)
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Price is required");
            if (!quantity)
                message.append(std::string((newLine > 0) ? "\n" : "") +
                               "Quantity is required");

            throw message + '\n';
        }

        sqlite3_stmt *stmt;
        std::string query{
            "UPDATE Items SET ref = ?, name = ?, price = ?, quantity = ? "
            "WHERE id = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to update item: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, item.ref.c_str(), item.ref.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, item.name.c_str(), item.name.length(), SQLITE_STATIC);
        sqlite3_bind_double(stmt, 3, item.price);
        sqlite3_bind_int(stmt, 4, item.quantity);
        sqlite3_bind_text(stmt, 5, item.id.c_str(), item.id.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to update item: " + std::string(sqlite3_errmsg(db)) + '\n';
    }
    void StorageItem::remove(std::string id)
    {
        if (id.empty())
            throw "Id is required\n";

        sqlite3_stmt *stmt;
        std::string query{
            "DELETE FROM Items WHERE id = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to remove item: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_STATIC);

        success = sqlite3_step(stmt);
        if (success != SQLITE_DONE)
            throw "SQLITE Error: to remove item: " + std::string(sqlite3_errmsg(db)) + '\n';
    }
    std::vector<Item> StorageItem::getItems(std::string idUser)
    {
        if (idUser.empty())
            throw "IdUser is required\n";

        sqlite3_stmt *stmt;
        std::string query{
            "SELECT * FROM Items "
            "WHERE idUser = ?"};

        int success{sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr)};
        if (success != SQLITE_OK)
            throw "SQLITE Error: to get items: " + std::string(sqlite3_errmsg(db)) + '\n';

        sqlite3_bind_text(stmt, 1, idUser.c_str(), idUser.length(), SQLITE_STATIC);

        std::vector<Item> items{};
        int row{0};
        while ((row = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            Item item;
            item.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            item.idUser = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            item.ref = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            item.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            item.price = sqlite3_column_double(stmt, 4);
            item.quantity = sqlite3_column_int(stmt, 5);
            item.isNull = false;

            items.push_back(item);
        }

        sqlite3_finalize(stmt);
        return items;
    }
}