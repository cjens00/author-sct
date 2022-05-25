#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/appCore]
// =========================================================
// Notes:
// =========================================================
#include "core/ui/renderer.h"
#include "core/ui/ui.h"

namespace Author
{
    class AppCore
    {
        Core::GUI *gui;
    public:
        AppCore();
        explicit AppCore(IVec2 windowSize);
        void Run();
    private:
        bool ShouldClose();
    };
}