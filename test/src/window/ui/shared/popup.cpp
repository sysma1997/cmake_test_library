#include "./popup.h"

#include <iostream>

char Popup::title[60];
char Popup::message[200];

void Popup::Show(std::string title, std::string message)
{
    strcpy(Popup::title, title.c_str());
    strcpy(Popup::message, message.c_str());

    ImGui::OpenPopup(title.c_str());
}
void Popup::Desing(std::function<void()> content)
{
    ImVec2 center{ImGui::GetMainViewport()->GetCenter()};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(message);
        ImGui::Separator();

        content();

        ImGui::EndPopup();
    }
}