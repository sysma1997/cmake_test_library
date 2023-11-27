#pragma once

#include "../../../libs/sysma/sysma.h"
#include "../../global.h"
#include "../../window/window.h"

class Profile
{
    static char name[100];
    static char phone[30];
    static char email[60];

    static bool isEdit;

public:
    static bool show;

    static void Init(Window window, sysma::Storage *storage);
};