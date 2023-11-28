#pragma once

#include <functional>
#include <string>

#include "../ui.h"

class Popup
{
    static char title[60];

public:
    static void Show(std::string title);
    static void Desing(std::function<void()> content);
};