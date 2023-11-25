#pragma once

#include <glm/glm.hpp>

#include "../../../libs/sysma/sysma.h"
#include "../../window/window.h"
#include "../login/login.h"

class Register
{
private:
    static char name[100];
    static char phone[30];
    static char email[60];
    static char password[60];
    static char passwordRepeat[60];

    static char modalTitle[60];
    static char modalMessage[200];

public:
    static bool show;
    static glm::vec2 size;

    static void Init(Window window, sysma::Database *storage);
};