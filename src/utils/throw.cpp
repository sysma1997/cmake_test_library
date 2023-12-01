#include "./throw.h"

namespace sysma
{
    Throw::Throw(bool valid, std::string message)
    {
        this->valid = valid;
        this->message = message;
    }
}