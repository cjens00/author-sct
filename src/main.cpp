// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================

#include "core/app_core.h"

int main()
{
    auto *app = new Author::AppCore();
    app->Run();

    return 0;
}