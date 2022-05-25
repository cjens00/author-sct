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
    struct UIElementTriggers
    {
        // Main Menu trigger
        bool showMainMenuBar = true;

        // Project View triggers
        bool showProjectViewWindow = true;
        bool projectViewTree_RootIsOpen = true;

        // Server Editor View triggers
        bool showServerEditorViewWindow = true;

        // Console View triggers
        bool showConsoleView = true;
    };

    class UI
    {
        /// ImGuiIO for quick access to ImGui fields
        ImGuiIO *io;

        /// The UI's rendering component, soon will
        /// support more than just GLFW/GL 3.3 core.
        Renderer *uiRenderer;

        /// Boolean triggers true for UI Windows/Menus
        /// drawn this frame.
        UIElementTriggers triggers;
        bool showImGuiDemoWindow = false;

        float yOffsetMainMenu = 0.0f;

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

        /// Advances the rendering of this UI by one frame.
        void Tick();

    private:
        ///
        void Draw();

        static inline void InstallStyle(bool usingDarkMode, float alpha);

        void ShowConsoleView();

        void ShowMainMenu();

        void ShowProjectView();

        void ShowServerEditorView();
    };
}
