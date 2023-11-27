#pragma once

#include <string>
#include <sqlite3.h>

#include "./storage/user.h"
#include "./storage/item.h"

namespace sysma
{
    class Storage
    {
        static sqlite3 *db;

    public:
        StorageUser user;
        StorageItem item;

        Storage();
        ~Storage();
    };
}