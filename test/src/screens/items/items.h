#pragma once

#include "../../../libs/sysma/sysma.h"
#include "../../global.h"
#include "../../window/window.h"

class Items
{
    static char ref[20];
    static char name[100];
    static double price;
    static int quantity;

public:
    static bool show;

    static void Init(Window window, sysma::Storage *storage);
};