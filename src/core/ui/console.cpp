#include "core/ui/console.h"

Console::Console()
{
    this->log = {};
    this->pos = 0;
    this->backlog = 0;
}

void Console::Write(const std::string &line)
{
    log[pos] = line + "\r\n";
    pos = ++pos == length ? 0 : pos;
    backlog++;
}

void Console::Read(std::string &buffer)
{
    for (int i = pos - 1; i >= (pos - backlog); i--)
    {
        buffer += log[i];
    }
    backlog = 0;
}
