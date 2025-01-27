#pragma once

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define MESHTOY_LOG_INFO(Message) Log::Write("INFO", __FILENAME__, __LINE__, Message)
#define MESHTOY_LOG_WARN(Message) Log::Write("WARN", __FILENAME__, __LINE__, Message)
#define MESHTOY_LOG_ERROR(Message) Log::Write("ERR!", __FILENAME__, __LINE__, Message)

#include <format>
#include <iostream>
#include <string>

class Log
{
public:
    static void Write(
        const std::string& Suffix,
        const std::string& File,
        const int Line,
        const std::string& Message
    )
    {
        std::cout << std::format("[{}][{}:{}] {}\n", Suffix, File, Line, Message);
    }
};
