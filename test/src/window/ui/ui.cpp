#include "./ui.h"

using namespace ImGui;

UI::UI(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    CreateContext();
    io = GetIO();
    (void)io;

    StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}
UI::~UI() {}

void UI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGuiStyle *style{&ImGui::GetStyle()};

    /* WINDOW */
    style->WindowRounding = 5.0f;
    style->WindowPadding = ImVec2(8.0f, 10.0f);
    style->WindowTitleAlign = ImVec2(0.5f, 0.5f);

    /* FRAME */
    style->FrameRounding = 2.0f;
    style->FramePadding = ImVec2(6.0f, 6.0f);

    NewFrame();
}
void UI::renderFrame()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
void UI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}