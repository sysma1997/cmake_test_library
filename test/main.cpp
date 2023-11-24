#include "./libs/sysma/sysma.h"
#include "./src/window/window.h"

#include "./src/screens/login/login.h"
#include "./src/screens/register/register.h"

int main()
{
    sysma::storage = sysma::Database();

    Window window{800, 600};
    window.init("test");
    UI ui{window.window};

    while (window.isClose())
    {
        window.newFrame();
        ui.newFrame();

        if (Login::show)
            Login::Init(window, &sysma::storage);
        if (Register::show)
            Register::Init(window, &sysma::storage);

        ui.renderFrame();
        window.renderFrame();
    }

    ui.terminate();
    window.terminate();

    return 0;
}