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
    this->ui = new Author::Core::UI(IVec2{.x = 1920, .y = 1200});
    this->ui->Init();
}

Author::AppCore::AppCore(IVec2 windowSize)
{
    this->ui = new Author::Core::UI(windowSize);
}

void Author::AppCore::Run()
{
    while (!ShouldClose())
    {
        this->ui->Tick();
    }
}

bool Author::AppCore::ShouldClose()
{
    return ui->shouldClose;
}
