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
/// TODO: Change the font to something tolerable.
/// TODO: Get a working console going.
/// TODO: Serialization and save system.
/// ======================================================================

Author::UI::UI::UI()
{
    uiRenderer = new Renderer();
    uiRenderer->Init("AUTHOR Early Preview || Developer Build", IVec2{.x=1920, .y=1200});
    io = nullptr;
    es = {};
    console = {};
    consoleBuf = "";
    appShouldClose = false;
}

Author::UI::UI::UI(IVec2 windowSize)
{
    uiRenderer = new Renderer();
    uiRenderer->Init("AUTHOR // Server Creation and Management Tool", windowSize);
    io = nullptr;
    es = {};
    console = {};
    consoleBuf = "";
    appShouldClose = false;
}

bool Author::UI::UI::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    (void) *io;

    ImGui::StyleColorsDark();
    io->FontGlobalScale = 1.75f;
    ImGui_ImplGlfw_InitForOpenGL(uiRenderer->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    InstallStyle(1.0f);

    return true;
}

void Author::UI::UI::Tick()
{
    // Check backend for appShouldClose event and update
    this->appShouldClose = this->uiRenderer->shouldClose;
    this->uiRenderer->Tick();

    // Start a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    this->Draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    this->uiRenderer->SwapBuffer();
}

Author::UI::UI::~UI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Author::UI::UI::Draw()
{
    // Update layout
    DrawLayout();

    // Draw the UI Menu/Windows.
    // Note: showMainMenuBar is always true, but this may change later.
    if (es.showMainMenuBar) ShowMainMenu();

    ShowExplorer();
    ShowEditor();
    ShowConsole();
}

void Author::UI::UI::ShowMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {}
            if (ImGui::MenuItem("Save"))
            {}
            if (ImGui::MenuItem("ImGui Demo"))
            {
                this->showImGuiDemoWindow = !this->showImGuiDemoWindow;
            }
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

void Author::UI::UI::ShowExplorer()
{
    ImGui::SetNextWindowPos(es.posWindowLeft);
    ImGui::SetNextWindowSize(es.sizeWindowLeft);
    ImGui::Begin("Explorer", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize
    );
    ImGui::End();
}

void Author::UI::UI::ShowEditor()
{
    ImGui::SetNextWindowPos(es.posWindowRight);
    ImGui::SetNextWindowSize(es.sizeWindowRight);
    ImGui::Begin("Editor", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize
    );
    ImGui::End();
}

void Author::UI::UI::ShowConsole()
{
    ImGui::SetNextWindowPos(es.posWindowConsole);
    ImGui::SetNextWindowSize(es.sizeWindowConsole);
    ImGui::Begin("Console", nullptr,
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse
    );
    es.counter++;
    if (es.counter % 80 == 0)
    {
        console.Write("Testing the console output");
        std::cout << "test\r\n";
    }
    console.Read(consoleBuf);
    ImGui::Text("%s", consoleBuf.c_str());
    ImGui::End();
}

void Author::UI::UI::DrawLayout()
{
    if (ImGui::BeginMainMenuBar())
    {
        es.mainMenuSize = ImGui::GetWindowSize();
        ImGui::EndMainMenuBar();
    }

    es.sizeWindowLeft.x = 0.25f * (io->DisplaySize.x);
    es.sizeWindowLeft.y = 0.75f * (io->DisplaySize.y - es.mainMenuSize.y);

    es.sizeWindowRight.x = 0.75f * (io->DisplaySize.x);
    es.sizeWindowRight.y = 0.75f * (io->DisplaySize.y - es.mainMenuSize.y);

    es.sizeWindowConsole.x = io->DisplaySize.x;
    es.sizeWindowConsole.y = 0.25f * (io->DisplaySize.y - es.mainMenuSize.y);
    es.posWindowRight.x = es.sizeWindowLeft.x;
    es.posWindowLeft.x = 0.0f;
    es.posWindowLeft.y = es.posWindowRight.y = es.mainMenuSize.y;
    es.posWindowConsole.y = es.sizeWindowLeft.y + es.mainMenuSize.y;
}

inline void Author::UI::UI::InstallStyle(float alpha)
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
}

