// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// Using Dear ImGui by Omar Cornut.
// Dear ImGui :: https://github.com/ocornut/imgui
// =========================================================
// [main]
// =========================================================
// Notes:
// =========================================================
#include "core/app_core.h"

int main()
{
    auto *app = new Author::AppCore();
    app->Run();

    return 0;
}


