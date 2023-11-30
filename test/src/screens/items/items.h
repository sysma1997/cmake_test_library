#pragma once

#include <vector>

#include "../../../libs/sysma/sysma.h"
#include "../../global.h"
#include "../../window/window.h"

class Items
{
    static char ref[20];
    static char name[100];
    static double price;
    static int quantity;

    static sysma::Item item;
    static std::vector<sysma::Item> items;

    static void add(sysma::Storage *storage);
    static void update(sysma::Storage *storage);

public:
    static bool show;

    static void Init(Window window, sysma::Storage *storage);
    static void getItems(sysma::Storage *storage);
};