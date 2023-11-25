#include "./login.h"

#include <iostream>

char Login::email[60]{""};
char Login::password[60]{""};

bool Login::show{true};
glm::vec2 Login::size{200.0f, 200.0f};

void Login::Init(Window window, sysma::Storage *storage)
{
    ImVec2 center{window.width / 2.0f, window.height / 2.0f};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Email:");
    ImGui::InputText("##email", email, IM_ARRAYSIZE(email));
    ImGui::Text("Password:");
    ImGui::InputText("##password", password, IM_ARRAYSIZE(password),
                     ImGuiInputTextFlags_Password);

    ImGui::NewLine();
    if (ImGui::Button("Login"))
    {
        /* sysma::User user{storage->user.login(email, password)};
        std::cout << "User: " << user.id << '\n'
                  << "name: " << user.name << '\n'
                  << "phone: " << user.phone << '\n'
                  << "email: " << user.email << '\n'
                  << "password: " << user.password << '\n'
                  << "is null: " << user.isNull << '\n'; */
    }
    ImGui::SameLine();
    if (ImGui::Button("Register"))
    {
        show = false;
        Register::show = true;
    }

    ImGui::End();
}