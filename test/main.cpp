#include <iostream>
#include <string>

#include "./libs/sysma/sysma.h"

#include "./src/global.h"
#include "./src/window/window.h"
#include "./src/screens/login/login.h"
#include "./src/screens/register/register.h"
#include "./src/screens/profile/profile.h"
#include "./src/screens/items/items.h"

int main()
{
    Global::user.isNull = true;
    try
    {
        Global::storage = sysma::Storage();
    }
    catch (std::string err)
    {
        std::cout << err << '\n';

        return -1;
    }

    std::string cacheLogin{sysma::File::Read("./cache/login.txt")};
    if (!cacheLogin.empty())
    {
        try
        {
            Global::user = Global::storage.user.get(cacheLogin);
            if (!Global::user.isNull)
                Login::show = false;
        }
        catch (std::string err)
        {
            std::cout << err << '\n';
        }
    }

    Window window{1200, 700};
    window.init("test");
    UI ui{window.window};

    bool showImGuiDemo{false};

    while (window.isClose())
    {
        window.newFrame(glm::vec3{0.1f, 0.1f, 0.1f});
        ui.newFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Window"))
            {
                std::string titleImGuiDemo{"ImGui demo: " + std::string((showImGuiDemo) ? "hide" : "show")};
                if (ImGui::MenuItem(titleImGuiDemo.c_str()))
                    showImGuiDemo = !showImGuiDemo;
                if (ImGui::MenuItem("Exit"))
                    window.isClose(true);

                ImGui::EndMenu();
            }
            if (!Global::user.isNull)
            {
                if (ImGui::BeginMenu(Global::user.name.c_str()))
                {
                    if (ImGui::MenuItem("Profile"))
                        Profile::show = true;
                    if (ImGui::MenuItem("Items"))
                    {
                        Items::show = true;
                        Items::getItems();
                    }
                    if (ImGui::MenuItem("Logout"))
                    {
                        Global::user = sysma::User{};
                        Global::user.isNull = true;
                        sysma::File::Remove("./cache/login.txt");

                        Login::show = true;
                    }

                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }

        if (showImGuiDemo)
            ImGui::ShowDemoWindow(&showImGuiDemo);
        if (Login::show)
            Login::Init(window);
        if (Register::show)
            Register::Init(window);
        if (Profile::show)
            Profile::Init(window);
        if (Items::show)
            Items::Init(window);

        ui.renderFrame();
        window.renderFrame();
    }

    ui.terminate();
    window.terminate();

    return 0;
}