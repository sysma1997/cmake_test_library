#include "./popup.h"

#include <iostream>

char Popup::title[60];

void Popup::Show(std::string title)
{
    strcpy(Popup::title, title.c_str());

    ImGui::OpenPopup(title.c_str());
}
void Popup::Desing(std::function<void()> content)
{
    ImVec2 center{ImGui::GetMainViewport()->GetCenter()};
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        content();

        ImGui::EndPopup();
    }
}