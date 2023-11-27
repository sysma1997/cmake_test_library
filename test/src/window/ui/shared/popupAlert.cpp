#include "./popupAlert.h"

char PopupAlert::title[60];
char PopupAlert::message[200];
std::function<void()> PopupAlert::ok = []() {};

void PopupAlert::Show(std::string title, std::string message, std::function<void()> ok)
{
    strcpy(PopupAlert::title, title.c_str());
    strcpy(PopupAlert::message, message.c_str());
    PopupAlert::ok = ok;

    ImGui::OpenPopup(title.c_str());
}
void PopupAlert::Desing()
{
    ImVec2 center{ImGui::GetMainViewport()->GetCenter()};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(message);
        ImGui::Separator();

        if (ImGui::Button("Ok"))
        {
            PopupAlert::ok();

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}