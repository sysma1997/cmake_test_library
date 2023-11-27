#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cstdio>

namespace sysma
{
    class File
    {
    public:
        static void Save(std::string path, std::string value);
        static std::string Read(std::string path);
        static void Remove(std::string path);
    };
}