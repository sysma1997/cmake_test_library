#pragma once

#include "../../../libs/sysma/sysma.h"
#include "../../global.h"
#include "../../window/window.h"
#include "../login/login.h"

class Profile
{
    static char name[100];
    static char phone[30];
    static char email[60];

    static char modalPassword[60];
    static char modalPasswordRepeat[60];
    static char modalMessage[200];
    static ImVec4 modalMessageColor;

    static bool isEdit;

public:
    static bool show;

    static void Init(Window window);
};