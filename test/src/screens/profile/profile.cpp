#include "./profile.h"

#include <iostream>

char Profile::name[100];
char Profile::phone[30];
char Profile::email[60];

char Profile::modalPassword[60];
char Profile::modalPasswordRepeat[60];
char Profile::modalMessage[200];
ImVec4 Profile::modalMessageColor;

bool Profile::isEdit = false;

bool Profile::show = false;

void Profile::Init(Window window, sysma::Storage *storage)
{
    ImGui::Begin("Profile", &show);
    ImGui::Text(std::string("Id: " + Global::user.id).c_str());
    ImGui::Text("Name: ");
    if (!isEdit)
    {
        ImGui::SameLine();
        ImGui::Text(Global::user.name.c_str());
    }
    else
        ImGui::InputText("##name", name, IM_ARRAYSIZE(name));
    ImGui::Text("Phone: ");
    if (!isEdit)
    {
        ImGui::SameLine();
        ImGui::Text(Global::user.phone.c_str());
    }
    else
        ImGui::InputText("##phone", phone, IM_ARRAYSIZE(phone));
    ImGui::Text("Email: ");
    if (!isEdit)
    {
        ImGui::SameLine();
        ImGui::Text(Global::user.email.c_str());
    }
    else
        ImGui::InputText("##email", email, IM_ARRAYSIZE(email));

    ImGui::NewLine();
    if (ImGui::Button((!isEdit) ? "Edit" : "Update"))
    {
        if (isEdit)
        {
            auto yes = [&]
            {
                sysma::User user{Global::user};
                user.name = name;
                user.phone = phone;
                user.email = email;
                try
                {
                    storage->user.update(user);
                    Global::user = user;
                    isEdit = !isEdit;
                }
                catch (std::string err)
                {
                    std::cout << err << '\n';
                }
            };
            PopupConfirm::Show("Update", "Update this information?", yes);
        }
        else
        {
            strcpy(name, Global::user.name.c_str());
            strcpy(phone, Global::user.phone.c_str());
            strcpy(email, Global::user.email.c_str());

            isEdit = !isEdit;
        }
    }
    if (isEdit)
    {
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            isEdit = !isEdit;
    }
    else
    {
        ImGui::SameLine();
        if (ImGui::Button("Update password"))
            Popup::Show("Update password");
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            auto yes = [&]
            {
                try
                {
                    storage->user.remove(Global::user.id);
                    Global::user = sysma::User{};
                    Global::user.isNull = true;
                    sysma::File::Remove("./cache/login.txt");

                    show = false;
                    Login::show = true;
                }
                catch (std::string err)
                {
                    std::cout << err << '\n';
                }
            };
            PopupConfirm::Show("Delete", "Delete me user?", yes);
        }
    }

    PopupAlert::Desing();
    PopupConfirm::Desing();
    auto content = [&]
    {
        auto clearForm = [&]
        {
            strcpy(modalPassword, "");
            strcpy(modalPasswordRepeat, "");
            strcpy(modalMessage, "");
        };
        ImGui::Text("New password:");
        ImGui::InputText("##password", modalPassword, IM_ARRAYSIZE(modalPassword),
                         ImGuiInputTextFlags_Password);
        ImGui::Text("Repeat new password:");
        ImGui::InputText("##passwordRepeat", modalPasswordRepeat, IM_ARRAYSIZE(modalPasswordRepeat),
                         ImGuiInputTextFlags_Password);

        if (modalMessage[0] != '\0')
        {
            ImGui::NewLine();
            ImGui::TextColored(modalMessageColor, modalMessage);
            ImGui::NewLine();
        }

        ImGui::Separator();
        if (ImGui::Button("Update"))
        {
            bool isValid{true};
            std::string _password{modalPassword};
            std::string _passwordRepeat{modalPasswordRepeat};
            if (_password.empty() ||
                _passwordRepeat.empty())
            {
                std::string message{""};

                int newLine{0};
                if (_password.empty())
                {
                    message.append("Password is required");
                    newLine++;
                }
                if (_passwordRepeat.empty())
                    message.append(std::string((newLine > 0) ? "\n" : "") +
                                   "Password repeat is required.");

                modalMessageColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                strcpy(modalMessage, message.c_str());
                isValid = false;
            }
            if (_password != _passwordRepeat)
            {
                modalMessageColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                strcpy(modalMessage, "new Password and repeat new password is not equals");
                isValid = false;
            }

            if (isValid)
            {
                strcpy(modalMessage, "");

                sysma::User user{Global::user};
                user.password = sysma::sha256(modalPassword);
                try
                {
                    storage->user.update(user);
                    Global::user = user;

                    clearForm();
                    modalMessageColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
                    strcpy(modalMessage, "Update password successfully");
                }
                catch (std::string err)
                {
                    modalMessageColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                    strcpy(modalMessage, err.c_str());
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            clearForm();
            ImGui::CloseCurrentPopup();
        }
    };
    Popup::Desing(content);
    ImGui::End();
}