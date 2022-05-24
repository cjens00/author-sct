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
#include "../../lib/imgui/include/imgui.h"
#include "../../lib/imgui/include/imgui_impl_glfw.h"
#include "../../lib/imgui/include/imgui_impl_opengl3.h"

#include "core/renderer.h"

namespace Author::Core
{
    typedef std::function<void()> windowFunction; // name could be better
    class GUIWindow
    {
    public:
        bool enabled;
        std::string name;
        windowFunction Draw;
    public:
        GUIWindow(windowFunction &wFunc, std::string wName, bool enabled);
        GUIWindow(windowFunction &&wFunc, std::string wName, bool enabled);
        void Toggle();
    };

    class GUI
    {
        std::vector<GUIWindow> windows;
    public:
        GUI();
        ~GUI();
        bool Init(Author::Core::Renderer *renderer);
        void AddWindow(GUIWindow w);
        void RemoveWindow(const std::string &name);
        GUIWindow *GetWindow(const std::string& name);
        void Tick();
    private:
        void InstallCoreWindows();
        static inline void InstallStyle(bool usingDarkMode, float alpha);
    };
}
