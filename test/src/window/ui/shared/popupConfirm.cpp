#include "./popupConfirm.h"

char PopupConfirm::title[60];
char PopupConfirm::message[200];
std::function<void()> PopupConfirm::yes = []() {};
std::function<void()> PopupConfirm::no = []() {};

void PopupConfirm::Show(std::string title, std::string message,
                        std::function<void()> yes, std::function<void()> no)
{
    strcpy(PopupConfirm::title, title.c_str());
    strcpy(PopupConfirm::message, message.c_str());
    PopupConfirm::yes = yes;
    PopupConfirm::no = no;

    ImGui::OpenPopup(title.c_str());
}
void PopupConfirm::Desing()
{
    ImVec2 center{ImGui::GetMainViewport()->GetCenter()};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(message);
        ImGui::Separator();

        if (ImGui::Button("Yes"))
        {
            PopupConfirm::yes();

            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No"))
        {
            PopupConfirm::no();

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}