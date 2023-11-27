#pragma once

#include <functional>
#include <string>

#include "../ui.h"
#include "./popup.h"

class PopupConfirm
{
    static char title[60];
    static char message[200];
    static std::function<void()> yes;
    static std::function<void()> no;

public:
    static void Show(
        std::string title,
        std::string message,
        std::function<void()> yes = []() {},
        std::function<void()> no = []() {});
    static void Desing();
};