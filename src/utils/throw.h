#pragma once

#include <string>

namespace sysma
{
    struct Throw
    {
        bool valid;
        std::string message;

        Throw(bool valid, std::string message);
    };
}