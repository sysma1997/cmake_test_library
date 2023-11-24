#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "./ui/ui.h"

class Window
{
public:
    int width;
    int height;
    GLFWwindow *window;

    Window(int width, int height);
    ~Window();

    void init(const char *title);
    bool isClose();
    void newFrame(glm::vec4 background = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};