#include "./profile.h"

char Profile::name[100];
char Profile::phone[30];
char Profile::email[60];

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
            sysma::User user{Global::user};
            user.name = name;
            user.phone = phone;
            user.email = email;
            try
            {
                storage->user.update(user);
                Global::user = user;
                isEdit = !isEdit;

                PopupAlert::Show("Update", "User update successfully");
            }
            catch (std::string err)
            {
                PopupAlert::Show("Warning", err);
            }
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
        {
            //
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            PopupConfirm::Show("Delete", "Delete me user?");
        }
    }

    PopupAlert::Desing();
    PopupConfirm::Desing();
    ImGui::End();
}