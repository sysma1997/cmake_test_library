#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

#include "../utils/throw.h"

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

        std::string toString();
    };

    class StorageItem
    {
        sqlite3 *db;

        Throw validate(Item item);

    public:
        void init(sqlite3 *db);
        void add(Item *item);
        void update(Item item);
        void remove(std::string id);
        std::vector<Item> getItems(std::string idUser);
        Item getRef(std::string idUser, std::string ref);
    };
}