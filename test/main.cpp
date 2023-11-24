#include "./libs/sysma/sysma.h"
#include "./src/window/window.h"

int main()
{
    sysma::storage = sysma::Database();

    Window window{800, 600};
    window.init("test");
    UI ui{window.window};

    char username[60]{""};
    char password[60]{""};

    while (window.isClose())
    {
        window.newFrame();
        ui.newFrame();

        ImGui::SetNextWindowPos(ImVec2(window.width / 2, window.height / 2));
        ImGui::Begin("login");
        ImGui::Text("Username:");
        ImGui::InputText("##username", username, IM_ARRAYSIZE(username));
        ImGui::Text("Password:");
        ImGui::InputText("##password", password, IM_ARRAYSIZE(password));
        ImGui::End();

        ui.renderFrame();
        window.renderFrame();
    }

    ui.terminate();
    window.terminate();

    return 0;
}