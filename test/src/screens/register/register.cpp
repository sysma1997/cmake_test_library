#include "./register.h"

char Register::name[100]{""};
char Register::phone[30]{""};
char Register::email[60]{""};
char Register::password[60]{""};
char Register::passwordRepeat[60]{""};

bool Register::show{false};
glm::vec2 Register::size{200.0f, 200.0f};

void Register::Init(Window window, sysma::Database *storage)
{
    glm::vec2 centerPos{
        (window.width / 2) - (size.x / 2),
        (window.height / 2) - (size.y / 2)};

    ImGui::SetNextWindowPos(ImVec2(centerPos.x, centerPos.y));
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    ImGui::Begin("Register", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Name:");
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
        storage->addUser(name, phone, email, password);
        show = false;
        Login::show = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Login"))
    {
        show = false;
        Login::show = true;
    }

    ImGui::End();
}