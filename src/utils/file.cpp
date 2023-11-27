#include "./file.h"

namespace sysma
{
    void File::Save(std::string path, std::string value)
    {
        if (path.find('/') != std::string::npos)
        {
            std::vector<std::string> paths{};

            size_t pos{0};
            std::string token;
            while ((pos = path.find("/")) != std::string::npos)
            {
                token = path.substr(0, pos);
                paths.push_back(token);
                path.erase(0, pos + 1);
            }

            std::string folder;
            int length = paths.size();
            for (int i{0}; i < length; i++)
                folder.append(paths[i] + std::string((i != length - 1) ? "/" : ""));

            int fail{mkdir(folder.c_str())};
            path = folder + "/" + path;
        }

        std::ofstream file{path.c_str()};
        file << value;
        file.close();
    }
    std::string File::Read(std::string path)
    {
        std::string result{""};

        std::string line;
        std::ifstream readFile{path.c_str()};
        while (std::getline(readFile, line))
            result.append(line + '\n');

        if (!result.empty() && result[result.length() - 1] == '\n')
            result.erase(result.length() - 1);

        return result;
    }
    void File::Remove(std::string path)
    {
        remove(path.c_str());
    }
}