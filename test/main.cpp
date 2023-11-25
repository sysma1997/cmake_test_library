#include <string>

#include "./libs/sysma/sysma.h"
#include "./src/window/window.h"

#include "./src/screens/login/login.h"
#include "./src/screens/register/register.h"

int main()
{
    sysma::Database storage{sysma::Database()};

    Window window{800, 600};
    window.init("test");
    UI ui{window.window};

    bool showImGuiDemo{false};

    while (window.isClose())
    {
        window.newFrame();
        ui.newFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem(std::string("ImGui demo: " + std::string((showImGuiDemo) ? "hide" : "show")).c_str()))
                    showImGuiDemo = !showImGuiDemo;
                if (ImGui::MenuItem("Exit"))
                    window.isClose(true);

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (showImGuiDemo)
            ImGui::ShowDemoWindow(&showImGuiDemo);
        if (Login::show)
            Login::Init(window, &storage);
        if (Register::show)
            Register::Init(window, &storage);

        ui.renderFrame();
        window.renderFrame();
    }

    ui.terminate();
    window.terminate();

    return 0;
}