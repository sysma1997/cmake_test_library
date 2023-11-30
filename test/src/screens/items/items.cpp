#include "./items.h"

#include <iostream>
#include <string>
#include <optional>

char Items::ref[20];
char Items::name[100];
double Items::price;
int Items::quantity;

sysma::Item Items::item;
std::vector<sysma::Item> Items::items;

void Items::add(sysma::Storage *storage)
{
    bool isValid{true};
    std::string _ref{ref};
    std::string _name{name};
    std::optional<double> _price{price};
    std::optional<int> _quantity{quantity};
    if (_ref.empty() ||
        _name.empty() ||
        !_price ||
        !_quantity)
    {
        isValid = false;

        std::string message{""};

        int newLine{0};
        if (_ref.empty())
        {
            message.append(std::string((newLine++ > 0) ? "\n" : "") +
                           "Reference is required");
            newLine++;
        }
        if (_name.empty())
            message.append(std::string((newLine++ > 0) ? "\n" : "") +
                           "Name is required");
        if (!price)
            message.append(std::string((newLine++ > 0) ? "\n" : "") +
                           "Price is required");
        if (!quantity)
            message.append(std::string((newLine > 0) ? "\n" : "") +
                           "Quantity is required");

        PopupAlert::Show("Invalid dates", message);
    }

    if (isValid)
    {
        try
        {
            sysma::Item newItem;
            newItem.idUser = Global::user.id;
            newItem.ref = ref;
            newItem.name = name;
            newItem.price = price;
            newItem.quantity = quantity;
            newItem.isNull = false;
            storage->item.add(&newItem);
            item = newItem;
            items.push_back(item);

            PopupAlert::Show("Info", "Item add successfully");
        }
        catch (std::string err)
        {
            PopupAlert::Show("Warning", err);
        }
    }
}
void Items::update(sysma::Storage *storage)
{
    //
}

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
    if (ImGui::Button(((item.isNull) ? "Add" : "Update")))
    {
        if (item.isNull)
            add(storage);
        else
            update(storage);
    }
    if (!item.isNull)
    {
        ImGui::SameLine();
        if (ImGui::Button("Remove"))
        {
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear"))
        {
            item = sysma::Item{};
            item.isNull = true;
            strcpy(ref, "");
            strcpy(name, "");
            price = 0.0;
            quantity = 0;
        }
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    // Table
    ImGui::BeginGroup();
    if (items.size() > 0)
    {
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

            for (int i{0}; i < items.size(); i++)
            {
                sysma::Item _item{items[i]};
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                if (ImGui::Selectable(_item.ref.c_str(), false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap))
                {
                    item = _item;
                    strcpy(ref, item.ref.c_str());
                    strcpy(name, item.name.c_str());
                    price = item.price;
                    quantity = item.quantity;
                }
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(_item.name.c_str());
                ImGui::TableSetColumnIndex(2);
                ImGui::Text(std::to_string(_item.price).c_str());
                ImGui::TableSetColumnIndex(3);
                ImGui::Text(std::to_string(_item.quantity).c_str());
            }
            /* for (int i{0}; i < 5; i++)
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
            } */

            ImGui::EndTable();
        }
    }
    else
    {
        ImGui::Text("There are no items created yet");
    }
    ImGui::EndGroup();

    PopupAlert::Desing();
    ImGui::End();
}
void Items::getItems(sysma::Storage *storage)
{
    item.isNull = true;
    items = storage->item.getItems(Global::user.id);
}