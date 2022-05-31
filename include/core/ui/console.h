#pragma once

#include <array>
#include <string>
#include <mutex>

class Console
{
    static const int length = 500;
    std::array<std::string, length> log;
    int pos;
    int backlog;
public:
    Console();
    void Write(const std::string& line);
    void Read(std::string &buffer);
};