#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================

#include "core/ui/ui.h"
#include "core/server.h"

namespace Author
{
    class AppCore
    {
        bool appShouldClose;
        UI::UI *ui;
        std::thread serverThread;
        Core::ServerLauncher serverLauncher;
    public:
        AppCore();
        explicit AppCore(IVec2 windowSize);
        void Run();
    };
}