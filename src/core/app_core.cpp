// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================

#include "core/app_core.h"

Author::AppCore::AppCore()
{
    this->appShouldClose = false;
    this->ui = new UI::UI(IVec2{.x = 1920, .y = 1200});
    this->ui->Init();
    this->serverLauncher = {};
}

Author::AppCore::AppCore(IVec2 windowSize)
{
    this->appShouldClose = false;
    this->ui = new UI::UI(windowSize);
    this->serverLauncher = {};
}

void Author::AppCore::Run()
{
    /// TODO: Start this in a new thread
    auto console = ui->GetConsole();
    serverThread = std::thread([&]()
                               {
                                   serverLauncher.Start(console);
                               });

    while (!(appShouldClose = ui->appShouldClose))
    {
        this->ui->Tick();
    }
    if (serverThread.joinable()) serverThread.join();
}
