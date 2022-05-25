// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/ui]
// =========================================================
// Notes:
// =========================================================
#include "core/ui/ui.h"
#include "core/ui/renderer.h"

#include <utility>

/// ======================================================================
/// TODO: GUI should have ownership of renderer. It is the only object using it.
/// ======================================================================

Author::Core::GUI::GUI(IVec2 windowSize)
{
    uiRenderer = new UIRenderer();
    uiRenderer->Init("AUTHOR // Server Creation and Management Tool", windowSize);
    windows = {};
    shouldClose = false;
}

bool Author::Core::GUI::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &imgui_io = ImGui::GetIO();
    (void) imgui_io;

    ImGui::StyleColorsDark();
    imgui_io.FontGlobalScale = 1.50f;
    ImGui_ImplGlfw_InitForOpenGL(uiRenderer->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    InstallStyle(true, 1.0f);
    InstallDefaultUIWindows();

    return true;
}

void Author::Core::GUI::AddWindow(UIWindow w)
{
    windows.emplace_back(std::move(w));
}

void Author::Core::GUI::RemoveWindow(const std::string &name)
{
    for (int i = 0; i < windows.size(); i++)
    {
        if (windows[i].name == name)
        {
            windows.erase(windows.begin() + i);
        }
    }
}

Author::Core::UIWindow *Author::Core::GUI::GetWindow(const std::string &name)
{
    for (auto &window: windows)
    {
        if (window.name == name)
        {
            return &window;
        }
    }
    return nullptr;
}

void Author::Core::GUI::Tick()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (const UIWindow &window: this->windows) window.Draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Check backend for close event and update
    this->shouldClose = uiRenderer->shouldClose;
}

Author::Core::GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Author::Core::GUI::InstallDefaultUIWindows()
{
    // =============== Begin Main Menu =================
    Author::Core::UIWindow mainMenu = Author::Core::UIWindow(
            Author::Core::OnDrawFunction(
                    [&]()
                    {
                        if (ImGui::BeginMainMenuBar())
                        {
                            if (ImGui::BeginMenu("File"))
                            {
                                if (ImGui::MenuItem("New"))
                                {}
                                if (ImGui::MenuItem("Save"))
                                {}
                                ImGui::EndMenu();
                            }
                            if (ImGui::BeginMenu("Edit"))
                            {
                                if (ImGui::MenuItem("Preferences"))
                                {}
                                ImGui::EndMenu();
                            }
                            ImGui::EndMainMenuBar();
                        }
                    }
            ),
            "MainMenu",
            true
    );
    this->AddWindow(mainMenu);
    // =============== End Main Menu ===================
    // =============== Begin Test Window ===============
    Author::Core::UIWindow testWindow = Author::Core::UIWindow(
            Author::Core::OnDrawFunction(
                    [&]()
                    {
                        ImGui::Begin("Test Window", &testWindow.enabled);
                        ImGui::Text("ImGui::Text");
                        if (ImGui::Button("ImGui::Button"))
                        {
                            std::cout << "On Button Clicked.\r\n";
                        }
                        ImGui::End();
                    }),
            "Test Window1",
            true);
    this->AddWindow(testWindow);
    // =============== End Test Window =================
}


/// =================================================================
/// Author::Core::UIWindow
/// =================================================================
/// TODO: Split GUI and UIWindow into separate files.
/// =================================================================
Author::Core::UIWindow::UIWindow(OnDrawFunction &wFunc, std::string wName, bool enabled)
{
    this->Draw = wFunc;
    this->name = std::move(wName);
    this->enabled = enabled;
}

Author::Core::UIWindow::UIWindow(OnDrawFunction &&wFunc, std::string wName, bool enabled)
{
    this->Draw = std::move(wFunc);
    this->name = std::move(wName);
    this->enabled = enabled;
}

void Author::Core::UIWindow::Toggle()
{
    this->enabled = !this->enabled;
}

inline void Author::Core::GUI::InstallStyle(bool usingDarkMode, float alpha)
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.Alpha = 1.0f;
    style.FrameRounding = 3.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    if (usingDarkMode)
    {
        for (int i = 0; i <= ImGuiCol_COUNT; i++)
        {
            ImVec4 &col = style.Colors[i];
            float H, S, V;
            ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

            if (S < 0.1f)
            {
                V = 1.0f - V;
            }
            ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
            if (col.w < 1.00f)
            {
                col.w *= alpha;
            }
        }
    } else
    {
        for (int i = 0; i <= ImGuiCol_COUNT; i++)
        {
            ImVec4 &col = style.Colors[i];
            if (col.w < 1.00f)
            {
                col.x *= alpha;
                col.y *= alpha;
                col.z *= alpha;
                col.w *= alpha;
            }
        }
    }
}