#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/appCore]
// =========================================================
// Notes:
// =========================================================
#include "renderer.h"
#include "ui.h"

namespace Author
{
    class AppCore
    {


        Core::Renderer *renderer;
        Core::GUI *gui;
    public:
        AppCore();
        AppCore(IVec2 windowSize);
        void Run();
    private:
        bool ShouldClose();
    };
}