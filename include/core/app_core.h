#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/appCore]
// =========================================================
// Notes:
// =========================================================
#include "core/ui/ui.h"
#include "core/server.h"

namespace Author
{
    class AppCore
    {
        bool appShouldClose;
        UI::UI *ui;
        Core::Server server;
    public:
        AppCore();
        explicit AppCore(IVec2 windowSize);
        void Run();
    };
}