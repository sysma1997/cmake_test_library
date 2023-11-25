#pragma once

#include <string>
#include <sqlite3.h>

#include "./storage/user.h"

namespace sysma
{
    class Storage
    {
        static sqlite3 *db;

    public:
        StorageUser user;

        Storage();
        ~Storage();
    };
}