#pragma once

#include <functional>
#include <string>

#include "../ui.h"
#include "./popup.h"

class PopupAlert
{
    static char title[60];
    static char message[200];
    static std::function<void()> ok;

public:
    static void Show(
        std::string title,
        std::string message,
        std::function<void()> ok = []() {});
    static void Desing();
};