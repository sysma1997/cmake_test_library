#pragma once

#include <GLFW/glfw3.h>

#include "../../../libs/imgui/imgui.h"
#include "../../../libs/imgui/imgui_impl_glfw.h"
#include "../../../libs/imgui/imgui_impl_opengl3.h"

#include "./shared/popup.h"
#include "./shared/popupAlert.h"
#include "./shared/popupConfirm.h"

class UI
{
public:
    ImGuiIO io;

    UI(GLFWwindow *window);
    ~UI();

    void newFrame();
    void renderFrame();
    void terminate();
};