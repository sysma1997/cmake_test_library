#pragma once

#include <functional>
#include <string>

#include "../ui.h"

class Popup
{
    static char title[60];
    static char message[200];

public:
    static void Show(std::string title, std::string message);
    static void Desing(std::function<void()> content);
};