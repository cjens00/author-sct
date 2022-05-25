// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/appCore]
// =========================================================
// Notes:
// =========================================================
#include "core/app_core.h"

Author::AppCore::AppCore()
{
    this->appShouldClose = false;
    this->ui = new UI::UI(IVec2{.x = 1920, .y = 1200});
    this->ui->Init();
}

Author::AppCore::AppCore(IVec2 windowSize)
{
    this->appShouldClose = false;
    this->ui = new UI::UI(windowSize);
}

void Author::AppCore::Run()
{
    while (!(appShouldClose = ui->appShouldClose))
    {
        this->ui->Tick();
    }
}
