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

    static void ClearForm();

public:
    static bool show;

    static void Init(Window window);
};