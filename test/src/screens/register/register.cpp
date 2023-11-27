#include "./register.h"

#include <iostream>
#include <string>
#include <functional>

char Register::name[100]{""};
char Register::phone[30]{""};
char Register::email[60]{""};
char Register::password[60]{""};
char Register::passwordRepeat[60]{""};

bool Register::show{false};

void Register::ClearForm()
{
    strcpy(name, "");
    strcpy(phone, "");
    strcpy(email, "");
    strcpy(password, "");
    strcpy(passwordRepeat, "");
}

void Register::Init(Window window, sysma::Storage *storage)
{
    ImVec2 center{window.width / 2.0f, window.height / 2.0f};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    ImGui::Begin("Register", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Name:");
    ImGui::PushItemWidth(200.0f * 0.9f);
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
            int newLine{0};
            if (_name.empty())
            {
                message.append("Name is required");
                newLine++;
            }
            if (_phone.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Phone is required");
            if (_email.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Email is required");
            if (_password.empty())
                message.append(std::string((newLine++ > 0) ? "\n" : "") +
                               "Password is required");
            if (_passwordRepeat.empty())
                message.append(std::string((newLine > 0) ? "\n" : "") +
                               "Repeat password is required");

            PopupAlert::Show("Invalid dates", message);
        }
        if (_password != _passwordRepeat)
        {
            isValid = false;

            PopupAlert::Show("Invalid dates", "Password and repeat password are not equal.");
        }

        if (isValid)
        {
            try
            {
                sysma::User user;
                user.name = name;
                user.phone = phone;
                user.email = email;
                user.password = sysma::sha256(password);
                storage->user.add(&user);
                Global::user = user;
                sysma::File::Save("./cache/login.txt", user.id);

                std::function<void()> ok = []()
                {
                    ClearForm();
                    show = false;
                };
                PopupAlert::Show("Info", "User register success.", ok);
            }
            catch (std::string err)
            {
                std::string message{""};
                if (err.find("Users.email", 0) != std::string::npos)
                    message = "Email already register";
                else
                    message = err;

                PopupAlert::Show("Invalid dates", message);
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Login"))
    {
        show = false;
        Login::show = true;
    }

    PopupAlert::Desing();
    ImGui::End();
}