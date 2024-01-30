#include "./login.h"

#include <iomanip>
#include <iostream>

#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

char Login::email[60]{""};
char Login::password[60]{""};

bool Login::show{true};

void Login::ClearForm()
{
    strcpy(email, "");
    strcpy(password, "");
}

void Login::Init(Window window)
{
    ImVec2 center{window.width / 2.0f, window.height / 2.0f};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Email:");
    ImGui::PushItemWidth(200.0f * 0.9f);
    ImGui::InputText("##email", email, IM_ARRAYSIZE(email));
    ImGui::Text("Password:");
    ImGui::InputText("##password", password, IM_ARRAYSIZE(password),
                     ImGuiInputTextFlags_Password);

    ImGui::NewLine();
    if (ImGui::Button("Login") ||
        ImGui::IsKeyPressed(ImGuiKey_Enter, false))
    {
        bool isValid{true};
        std::string _email{email};
        std::string _password{password};

        if (_email.empty() ||
            _password.empty())
        {
            isValid = false;

            std::string message{""};
            if (_email.empty())
                message.append("Email is required");
            if (_password.empty())
                message.append(std::string((_email.empty()) ? "\n" : "") + "Password is required");

            PopupAlert::Show("Invalid dates", message);
        }

        if (isValid)
        {
            try
            {
                Global::user = Global::storage.user.login(email, sysma::sha256(password));
                if (!Global::user.isNull)
                {
                    sysma::File::Save("./cache/login.txt", Global::user.id);

                    show = false;
                    ClearForm();
                }
                else
                    PopupAlert::Show("Info", "User not found, email or password incorrect");
            }
            catch (std::string err)
            {
                PopupAlert::Show("Warning", err);
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Register"))
    {
        show = false;
        Register::show = true;
    }

    PopupAlert::Desing();
    ImGui::End();
}