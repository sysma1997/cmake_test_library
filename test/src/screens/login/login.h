#pragma once

#include "../../../libs/sysma/sysma.h"
#include "../../global.h"
#include "../../window/window.h"
#include "../register/register.h"

class Login
{
    static char email[60];
    static char password[60];

    static void ClearForm();

public:
    static bool show;

    static void Init(Window window, sysma::Storage *storage);
};