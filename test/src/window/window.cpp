#include "./window.h"

#include <iostream>

Window::Window(int width, int height)
{
    this->width = width;
    this->height = height;
}
Window::~Window() {}

void Window::init(const char *title)
{
    if (!glfwInit())
    {
        std::cout << "WINDOW::init:: Failed init GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "WINDOW::init:: Error to open window with GLFW, if use old GPU, "
                  << "it's not compatible with OpenGL 3.3\n";
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = true;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "WINDOW::init:: Error to init GLEW.\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);
}
bool Window::isClose(bool exit)
{
    if (exit)
        glfwSetWindowShouldClose(window, true);

    return glfwWindowShouldClose(window) == 0;
}
void Window::newFrame(glm::vec4 background)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(background.x, background.y, background.z, background.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::renderFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Window::terminate()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::setKeyCallback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(window, callback);
}