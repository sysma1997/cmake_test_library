#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

namespace sysma
{
    struct Item
    {
        std::string id;
        std::string idUser;
        std::string ref;
        std::string name;
        double price;
        int quantity;

        bool isNull;
    };

    class StorageItem
    {
        sqlite3 *db;

    public:
        void init(sqlite3 *db);
        void add(Item *item);
        void update(Item item);
        void remove(std::string id);
        std::vector<Item> getItems(std::string idUser);
    };
}