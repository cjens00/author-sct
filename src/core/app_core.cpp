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
    this->gui = new Author::Core::GUI(IVec2{.x = 1920, .y = 1200});
    this->gui->Init();
}

Author::AppCore::AppCore(IVec2 windowSize)
{
    this->gui = new Author::Core::GUI(windowSize);
}

void Author::AppCore::Run()
{
    while (!ShouldClose())
    {
        this->gui->Tick();
    }
}

bool Author::AppCore::ShouldClose()
{
    return gui->shouldClose;
}
