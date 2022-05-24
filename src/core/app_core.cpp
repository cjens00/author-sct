#include "core/app_core.h"

Author::AppCore::AppCore()
{
    this->renderer = new Author::Core::Renderer();
    this->renderer->Init("AUTHOR (Working Title) - "
                         "Authoritative Server Creation Tool",
                         IVec2{.x = 1920, .y = 1200});

    this->gui = new Author::Core::GUI();
    this->gui->Init(this->renderer);
}

Author::AppCore::AppCore(IVec2 windowSize)
{
    this->renderer = new Author::Core::Renderer();
    this->renderer->Init("AUTHOR (Working Title) - "
                         "Authoritative Server Creation Tool",
                         windowSize);
    this->gui = new Author::Core::GUI();
    this->gui->Init(this->renderer);
}

void Author::AppCore::Run()
{
    while (!ShouldClose())
    {
        this->renderer->Tick();
        this->gui->Tick();
    }
}

bool Author::AppCore::ShouldClose()
{
    return this->renderer->ShouldClose();
}
