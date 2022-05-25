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
#include <functional>
#include <optional>

// ImGui Headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "renderer.h"

namespace Author::Core
{
    typedef std::function<void()> OnDrawFunction;
    class UIWindow
    {
    public:
        bool enabled;
        std::string name;
        OnDrawFunction Draw;
    public:
        UIWindow(OnDrawFunction &wFunc, std::string wName, bool enabled);

        UIWindow(OnDrawFunction &&wFunc, std::string wName, bool enabled);

        void Toggle();
    };

    class UI
    {
        Core::UIRenderer *uiRenderer;
        std::vector<UIWindow> windows;
    public:
        bool shouldClose;
    public:
        UI(IVec2 windowSize);

        ~UI();

        bool Init();

        void AddWindow(UIWindow w);

        void RemoveWindow(const std::string &name);

        UIWindow *GetWindow(const std::string &name);

        void Tick();

    private:
        void InstallDefaultUIWindows();

        static inline void InstallStyle(bool usingDarkMode, float alpha);
    };
}
