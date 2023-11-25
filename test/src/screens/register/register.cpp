#include "./register.h"

#include <iostream>
#include <string>

char Register::name[100]{""};
char Register::phone[30]{""};
char Register::email[60]{""};
char Register::password[60]{""};
char Register::passwordRepeat[60]{""};

char Register::modalTitle[60]{""};
char Register::modalMessage[200]{""};

bool Register::show{false};
glm::vec2 Register::size{200.0f, 0.0f};

void Register::Init(Window window, sysma::Storage *storage)
{
    ImVec2 center{window.width / 2.0f, window.height / 2.0f};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    ImGui::Begin("Register", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Name:");
    ImGui::PushItemWidth(size.x * 0.9f);
    ImGui::InputText("##name", name, IM_ARRAYSIZE(name));
    ImGui::Text("Phone:");
    ImGui::InputText("##phone", phone, IM_ARRAYSIZE(phone));
    ImGui::Text("Email:");
    ImGui::InputText("##email", email, IM_ARRAYSIZE(email));
    ImGui::Text("Password:");
    ImGui::InputText("##password", password, IM_ARRAYSIZE(password),
                     ImGuiInputTextFlags_Password);
    ImGui::Text("Repeat password:");
    ImGui::InputText("##passwordRepeat", passwordRepeat, IM_ARRAYSIZE(passwordRepeat),
                     ImGuiInputTextFlags_Password);

    ImGui::NewLine();
    if (ImGui::Button("Register"))
    {
        bool isValid{true};
        std::string _name{name};
        std::string _phone{phone};
        std::string _email{email};
        std::string _password{password};
        std::string _passwordRepeat{passwordRepeat};

        if (_name.empty() ||
            _phone.empty() ||
            _email.empty() ||
            _password.empty() ||
            _passwordRepeat.empty())
        {
            isValid = false;

            std::string message{""};
            if (_name.empty())
                message.append("Name is required");
            if (_phone.empty())
                message.append(std::string((_name.empty()) ? "\n" : "") +
                               "Phone is required");
            if (_email.empty())
                message.append(std::string((_name.empty() || _phone.empty()) ? "\n" : "") +
                               "Email is required");
            if (_password.empty())
                message.append(std::string((_name.empty() || _phone.empty() || _email.empty()) ? "\n" : "") +
                               "Password is required");
            if (_passwordRepeat.empty())
                message.append(std::string((_name.empty() || _phone.empty() || _email.empty() || _password.empty()) ? "\n" : "") +
                               "Repeat password is required");

            strcpy(modalTitle, "Invalid dates");
            strcpy(modalMessage, message.c_str());
            ImGui::OpenPopup(modalTitle);
        }
        if (_password != _passwordRepeat)
        {
            isValid = false;

            strcpy(modalTitle, "Invalid dates");
            strcpy(modalMessage, "Password and repeat password are not equal.");
            ImGui::OpenPopup(modalTitle);
        }

        if (isValid)
        {
            try
            {
                storage->user.add(name, phone, email, password);

                strcpy(modalTitle, "Info");
                strcpy(modalMessage, "User register success.");
                ImGui::OpenPopup(modalTitle);
            }
            catch (std::string err)
            {
                strcpy(modalTitle, "Invalid dates");
                if (err.find("Users.email", 0) != std::string::npos)
                    strcpy(modalMessage, "User already register");
                else
                    strcpy(modalMessage, err.c_str());
                ImGui::OpenPopup(modalTitle);
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Login"))
    {
        show = false;
        Login::show = true;
    }

    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(modalTitle, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(modalMessage);
        ImGui::Separator();

        if (ImGui::Button("Ok", ImVec2(100.0f, 0.0f)))
        {
            if (strcmp(modalTitle, "Info") == 0)
            {
                show = false;
                Login::show = true;
            }

            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}