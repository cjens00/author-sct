#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/ui]
// =========================================================
// Notes:
// =========================================================

// Standard Library Headers
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>

// ImGui Headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "renderer.h"

namespace Author::UI
{
    struct ElementState
    {
        // Main Menu trigger
        bool showMainMenuBar = true;

        // Console trigger
        bool showConsole = true;
    };

    class UI
    {
        /// ImGuiIO for quick access to ImGui fields
        ImGuiIO *io;

        /// Keeps track of UI element size & position, flags, etc.
        ElementState es;

        /// The UI's rendering component, soon will
        /// support more than just GLFW/GL 3.3 core.
        Renderer *uiRenderer;

        bool showImGuiDemoWindow = false;

    public:

        /// True when the user has requested to close
        /// the application in a normal manner.
        bool appShouldClose;

    public:
        /// Creates a new UI for the CoreApp. Default window size: 1920 x 1200.
        UI();

        /// Creates a new UI for the CoreApp with the specified window size.
        explicit UI(IVec2 windowSize);

        /// Destroys this UI along with its ImGui context.
        ~UI();

        /// Initializes backend components that the UI depends on.
        bool Init();

        /// Advances the rendering of this UI by one frame. ~~
        void Tick();

    private:

        /// ----------------------------
        void Draw();

        /// ----------------------------
        ImVec2 ShowMainMenu();

        /// Dynamic layout sizing and positioning by
        /// using DrawLayout to update ElementState.
        void DrawLayout();

        /// ----------------------------
        static inline void InstallStyle(bool usingDarkMode, float alpha);
    };
}
