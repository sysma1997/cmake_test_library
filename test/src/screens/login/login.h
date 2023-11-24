#pragma once

#include <glm/glm.hpp>

#include "../../../libs/sysma/sysma.h"
#include "../../window/window.h"
#include "../register/register.h"

class Login
{
    static char email[60];
    static char password[60];

public:
    static bool show;
    static glm::vec2 size;

    static void Init(Window window, sysma::Database *storage);
};