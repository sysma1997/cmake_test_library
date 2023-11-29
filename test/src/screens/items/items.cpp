#include "./items.h"

#include <iostream>
#include <string>

char Items::ref[20];
char Items::name[100];
double Items::price;
int Items::quantity;

bool Items::show{false};

void Items::Init(Window window, sysma::Storage *storage)
{
    ImVec2 size{window.width * 0.5f, 0.0f};
    ImGui::SetNextWindowSize(size);
    ImGui::Begin("Items", &show);

    // Form
    ImGui::PushItemWidth(size.x * 0.4f);
    ImGui::BeginGroup();
    ImGui::Text("Reference:");
    ImGui::InputText("##ref", ref, IM_ARRAYSIZE(ref));
    ImGui::Text("Name:");
    ImGui::InputText("##name", name, IM_ARRAYSIZE(name));
    ImGui::Text("Price:");
    ImGui::InputDouble("##price", &price, 0.0);
    ImGui::Text("Quantity:");
    ImGui::InputInt("##quantity", &quantity);
    ImGui::EndGroup();

    ImGui::SameLine();

    // Table
    ImGui::BeginGroup();
    if (ImGui::BeginTable("items", 4,
                          ImGuiTableFlags_RowBg |
                              ImGuiTableFlags_Borders |
                              ImGuiTableFlags_BordersV |
                              ImGuiTableFlags_BordersOuter |
                              ImGuiTableFlags_BordersInner))
    {
        ImGui::TableSetupColumn("Reference");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Price");
        ImGui::TableSetupColumn("Quantity");
        ImGui::TableHeadersRow();

        for (int i{0}; i < 5; i++)
        {
            ImGui::TableNextRow();
            for (int column{0}; column < 4; column++)
            {
                ImGui::TableSetColumnIndex(column);
                std::string text{"item " + std::to_string(i + 1) + " " + std::to_string(column + 1)};
                if (ImGui::Selectable(text.c_str(), false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap))
                {
                    std::cout << "Level\n";
                }
            }
        }

        ImGui::EndTable();
    }
    ImGui::EndGroup();

    ImGui::End();
}